#include<bits/stdc++.h>
using namespace std;

using ll = long long;
namespace PollardRho {
  mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
  const int P = 1e6 + 9;
  ll seq[P];
  int primes[P], spf[P];
  inline ll add_mod(ll x, ll y, ll m) {
    return x >= m-y ? x-(m-y) : x+y;
  }
  inline ll mul_mod(ll x, ll y, ll m) {
    ll res = __int128(x) * y % m;
    return res;
    // ll res = x * y - (ll)((long double)x * y / m + 0.5) * m;
    // return res < 0 ? res + m : res;
  }
  inline ll pow_mod(ll x, ll n, ll m) {
    ll res = 1 % m;
    for (; n; n >>= 1) {
      if (n & 1) res = mul_mod(res, x, m);
      x = mul_mod(x, x, m);
    }
    return res;
  }
  // O(it * (logn)^3), it = number of rounds performed
  inline bool miller_rabin(ll n) {
    if(n<2) return false;
    for (ll p : {2,3,5,7,11,13,17,19,23,29,31,37}) if(n%p==0) return n==p;
    ll d=n-1;
    int s=0;
    while(!(d&1)) { d>>=1; ++s; }
    for(ll a : {2LL,325LL,9375LL,28178LL,450775LL,9780504LL,1795265022LL}) {
      if(a%n==0) continue;
      ll x=pow_mod(a%n,d,n);
      if(x==1 || x==n-1) continue;
      bool passed=false;
      for(int k=1;k<s;++k) {
        x=mul_mod(x,x,n);
        if(x==n-1) { passed=true; break; }
      }
      if(!passed) return false;
    }
    return true;
  }
  void init() {
    if(spf[2]) return;
    int cnt = 0;
    for (int i = 2; i < P; i++) {
      if (!spf[i]) primes[cnt++] = spf[i] = i;
      for (int j = 0, k; (k = i * primes[j]) < P; j++) {
        spf[k] = primes[j];
        if (spf[i] == spf[k]) break;
      }
    }
  }
  // returns O(n^(1/4))
  ll pollard_rho(ll n) {
    while (1) {
      ll x = rnd() % n, y = x, c = rnd() % n, u = 1, v, t = 0;
      ll *px = seq, *py = seq;
      while (1) {
        *py++ = y = add_mod(mul_mod(y, y, n), c, n);
        *py++ = y = add_mod(mul_mod(y, y, n), c, n);
        if ((x = *px++) == y) break;
        v = u;
        u = mul_mod(u, abs(y - x), n);
        if (!u) return __gcd(v, n);
        if (++t == 32) {
          t = 0;
          if ((u = __gcd(u, n)) > 1 && u < n) return u;
        }
      }
      if (t && (u = __gcd(u, n)) > 1 && u < n) return u;
    }
  }
  vector<ll> factorize(ll n) {
    if (n == 1) return vector <ll>();
    if (miller_rabin(n)) return vector<ll> {n};
    vector <ll> v, w;
    while (n > 1 && n < P) {
      v.push_back(spf[n]);
      n /= spf[n];
    }
    if (n >= P) {
      ll x = pollard_rho(n);
      v = factorize(x);
      w = factorize(n / x);
      v.insert(v.end(), w.begin(), w.end());
    }
    return v;
  }
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  PollardRho::init();
  int t; cin >> t;
  while (t--) {
    ll n; cin >> n;
    auto f = PollardRho::factorize(n);
    sort(f.begin(), f.end());
    cout << f.size() << ' '; 
    for (auto x: f) cout << x << ' '; cout << '\n';
  }
  return 0;
}
// https://judge.yosupo.jp/problem/factorize

// Unsigned 64-bit factorization using Montgomery multiplication.
namespace montgomery {
struct Mint {
  uint64_t n;
  static uint64_t mod, inv, r2;
  Mint() : n(0) { }
  Mint(const uint64_t &x) : n(init(x)) { }
  static uint64_t init(const uint64_t &w) { return reduce(__uint128_t(w) * r2); }
  static void set_mod(const uint64_t &m) {
    mod = inv = m;
    for(int i = 0; i < 5; i++)  inv *= 2 - inv * m;
    r2 = -__uint128_t(m) % m;
  }
  static uint64_t reduce(const __uint128_t &x) {
    uint64_t y = uint64_t(x >> 64) - uint64_t((__uint128_t(uint64_t(x) * inv) * mod) >> 64);
    return int64_t(y) < 0 ? y + mod : y;
  }
  Mint& operator+= (const Mint &x) { n += x.n - mod; if(int64_t(n) < 0) n += mod; return *this; }
  Mint& operator+ (const Mint &x) const { return Mint(*this) += x; }
  Mint& operator*= (const Mint &x) { n = reduce(__uint128_t(n) * x.n); return *this; }
  Mint& operator* (const Mint &x) const { return Mint(*this) *= x; }
  uint64_t val() const { return reduce(n); }
};

uint64_t Mint::mod, Mint::inv, Mint::r2;

bool suspect(const uint64_t &a, const uint64_t &s, uint64_t d, const uint64_t &n) {
  if(Mint::mod != n)  Mint::set_mod(n);
  Mint x(1), xx(a), one(x), minusone(n - 1);
  while(d > 0) {
    if(d & 1) x *= xx;
    xx *= xx;
    d >>= 1;
  }
  if(x.n == one.n)  return true;
  for(unsigned int r = 0; r < s; r++) {
    if(x.n == minusone.n) return true;
    x *= x;
  }
  return false;
}

bool is_prime(const uint64_t &n) {
  if(n <= 1 || (n > 2 && (~n & 1))) return false;
  uint64_t d = n - 1, s = 0;
  while(~d & 1) s++, d >>= 1;
  static const uint64_t a_big[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  static const uint64_t a_smol[] = {2, 7, 61};
  if(n <= 4759123141LL) {
    for(auto &&p : a_smol) {
      if(p >= n)  break;
      if(!suspect(p, s, d, n))  return false;
    }
  } else {
    for(auto &&p : a_big) {
      if(p >= n)  break;
      if(!suspect(p, s, d, n))  return false;
    }
  }
  return true;
}

uint64_t rho_pollard(const uint64_t &n) {
  if(~n & 1)  return 2u;
  static random_device rng;
  uniform_int_distribution<uint64_t> rr(1, n - 1);
  if(Mint::mod != n)  Mint::set_mod(n);
  for(;;) {
    uint64_t c_ = rr(rng), g = 1, r = 1, m = 500;
    Mint y(rr(rng)), xx(0), c(c_), ys(0), q(1);
    while(g == 1) {
      xx.n = y.n;
      for(unsigned int i = 1; i <= r; i++)  y *= y, y += c;
      uint64_t k = 0; g = 1;
      while(k < r && g == 1) {
        for(unsigned int i = 1; i <= (m > (r - k) ? (r - k) : m); i++) {
          ys.n = y.n;
          y *= y; y += c;
          uint64_t xxx = xx.val(), yyy = y.val();
          q *= Mint(xxx > yyy ? xxx - yyy : yyy - xxx);
        }
        g = __gcd<uint64_t>(q.val(), n);
        k += m;
      }
      r *= 2;
    }
    if(g == n)  g = 1;
    while(g == 1) {
      ys *= ys; ys += c;
      uint64_t xxx = xx.val(), yyy = ys.val();
      g = __gcd<uint64_t>(xxx > yyy ? xxx - yyy : yyy - xxx, n);
    }
    if(g != n && is_prime(g)) return g;
  }
  assert(69 == 420);
}

template <typename T>
vector<T> factor(T n) {
  if(n < 2) return { };
  if(is_prime(n)) return {n};
  T d = rho_pollard(static_cast<uint64_t>(n));
  vector<T> l = factor(d), r = factor(n / d);
  l.insert(l.end(), r.begin(), r.end());
  return l;
}

//credit: olaf
int example() {
  int t; cin >> t;
  while(t--) {
    uint64_t n; cin >> n;
    vector<uint64_t> fac = factor(n);
    sort(fac.begin(), fac.end());
    cout << fac.size() << ' ';
    for(auto &&f : fac) {
      cout << f << ' ';
    }
    cout << '\n';
  }
  return 0;
}
// https://judge.yosupo.jp/problem/factorize
}
