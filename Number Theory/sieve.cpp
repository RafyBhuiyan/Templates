#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll N = 1e6 + 1;
int spf[N], vis[N], maxx[N];
vector<int>vp;
void sieve()
{
    if (spf[1]) return;
    vp.push_back(2);
    spf[1] = 1;
    spf[2] = 2;
    for (int i = 4; i < N; i += 2) spf[i] = 2;
    for (ll i = 3; i < N; i += 2)
    {
        if (vis[i]) continue;
        vp.push_back(i);
        spf[i] = i;
        for (ll j = i * i; j < N; j += 2 * i)
        {
            if (!vis[j])
            {
                vis[j] = 1;
                spf[j] = i;
            }
        }
    }
}
vector<ll> pfactor(ll n)
{
    assert(1 <= n && n < N);
    vector<ll>v;
    while (spf[n] != 1)
    {
        v.push_back(spf[n]);
        n /= spf[n];
    }
    return v;
}

// Alternative O(N) construction of the same smallest-prime-factor table.
void sieve_linear() {
    if (spf[1]) return;
    spf[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!spf[i]) { spf[i] = i; vp.push_back(i); }
        for (int p : vp) {
            if (p > spf[i] || 1LL * i * p >= N) break;
            spf[i*p] = p;
        }
    }
}
bool is_prime(int x) { return x >= 2 && x < N && spf[x] == x; }

// credit: min_25
// takes 0.5s for n = 1e9
vector<int> fastSieve(const int N, const int Q = 17, const int L = 1 << 15) {
  if (N < 30) {
    vector<int> small;
    for (int p : {2,3,5,7,11,13,17,19,23,29}) if (p <= N) small.push_back(p);
    return small;
  }
  static const int rs[] = {1, 7, 11, 13, 17, 19, 23, 29};
  struct P { 
    P(int p) : p(p) {}
    int p; int pos[8];
  };
  auto approx_prime_count = [] (const int N) -> int {
    return N > 60184 ? N / (log(N) - 1.1)
                     : max(1., N / (log(N) - 1.11)) + 1;
  };

  const int v = sqrt(N), vv = sqrt(v);
  vector<bool> isp(v + 1, true);
  for (int i = 2; i <= vv; ++i) if (isp[i]) {
    for (int j = i * i; j <= v; j += i) isp[j] = false;
  }

  const int rsize = approx_prime_count(N + 30);
  vector<int> primes = {2, 3, 5}; int psize = 3;
  primes.reserve(rsize);

  vector<P> sprimes; size_t pbeg = 0;
  int prod = 1; 
  for (int p = 7; p <= v; ++p) {
    if (!isp[p]) continue;
    if (p <= Q) { prod *= p; ++pbeg; primes.push_back(p); }
    auto pp = P(p); 
    for (int t = 0; t < 8; ++t) {
      int j = (p <= Q) ? p : p * p;
      while (j % 30 != rs[t]) j += p << 1;
      pp.pos[t] = j / 30;
    }
    sprimes.push_back(pp);
  }

  vector<unsigned char> pre(prod, 0xFF);
  for (size_t pi = 0; pi < pbeg; ++pi) {
    auto pp = sprimes[pi]; const int p = pp.p;
    for (int t = 0; t < 8; ++t) {
      const unsigned char m = ~(1 << t);
      for (int i = pp.pos[t]; i < prod; i += p) pre[i] &= m;
    }
  }

  const int block_size = (L + prod - 1) / prod * prod;
  vector<unsigned char> block(block_size);
  const int M = (N + 29) / 30;

  for (int beg = 0; beg < M; beg += block_size) {
    int end = min(M, beg + block_size);
    for (int i = beg; i < end; i += prod) {
      copy(pre.begin(), pre.end(), block.data() + (i-beg));
    }
    if (beg == 0) block[0] &= 0xFE;
    for (size_t pi = pbeg; pi < sprimes.size(); ++pi) {
      auto& pp = sprimes[pi];
      const int p = pp.p;
      for (int t = 0; t < 8; ++t) {
        int i = pp.pos[t]; const unsigned char m = ~(1 << t);
        for (; i < end; i += p) block[i-beg] &= m;
        pp.pos[t] = i;
      }
    }
    for (int i = beg; i < end; ++i) {
      for (int m = block[i-beg]; m > 0; m &= m - 1) {
        primes.push_back(i * 30 + rs[__builtin_ctz(m)]);
      }
    }
  }
  psize=primes.size();
  while (psize > 0 && primes[psize - 1] > N) --psize;
  primes.resize(psize);
  return primes;
}
