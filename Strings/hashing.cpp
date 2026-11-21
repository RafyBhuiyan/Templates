#include <bits/stdc++.h>
using namespace std;

const int N = 1e6+9;
const int  mod1 = 127657753, mod2 = 987654319;
int p1,p2;
using ll = long long;

int power(long long n, long long k, int mod)
{
    int ans = 1 % mod;
    n %= mod;
    if (n < 0) n += mod;
    while (k)
    {
        if (k & 1) ans = (long long) ans * n % mod;
        n = (long long) n * n % mod;
        k >>= 1;
    }
    return ans;
}

int ip1, ip2;
pair<int, int> pw[N], ipw[N];
void prec()
{
    if (p1) return;
    mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
    p1 = (500 + (rnd() % (mod1-500*2+1)));
    p2 = 0;
    do
    {
        p2 = (500 + (rnd() % (mod2-500*2+1)));
    }
    while (p1 == p2);
    pw[0] =  {1, 1};
    for (int i = 1; i < N; i++)
    {
        pw[i].first = 1LL * pw[i - 1].first * p1 % mod1;
        pw[i].second = 1LL * pw[i - 1].second * p2 % mod2;
    }
    ip1 = power(p1, mod1 - 2, mod1);
    ip2 = power(p2, mod2 - 2, mod2);
    ipw[0] =  {1, 1};
    for (int i = 1; i < N; i++)
    {
        ipw[i].first = 1LL * ipw[i - 1].first * ip1 % mod1;
        ipw[i].second = 1LL * ipw[i - 1].second * ip2 % mod2;
    }
}

pair<int, int> string_hash(string s)
{
    int n = s.size();
    pair<int, int> hs({0, 0});
    for (int i = 0; i < n; i++)
    {
        hs.first += 1LL * (unsigned char)s[i] * pw[i].first % mod1;
        hs.first %= mod1;
        hs.second += 1LL * (unsigned char)s[i] * pw[i].second % mod2;
        hs.second %= mod2;
    }
    return hs;
}
pair<int, int> pref[N];
void build(string s)
{
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        pref[i].first = 1LL * (unsigned char)s[i] * pw[i].first % mod1;
        if (i) pref[i].first = (pref[i].first + pref[i - 1].first) % mod1;
        pref[i].second = 1LL * (unsigned char)s[i] * pw[i].second % mod2;
        if (i) pref[i].second = (pref[i].second + pref[i - 1].second) % mod2;
    }
}
pair<int, int> gethash(int i, int j)
{
    pair<int, int> hs({0, 0});
    hs.first = pref[j].first;
    if (i) hs.first = (hs.first - pref[i - 1].first + mod1) % mod1;
    hs.first = 1LL * hs.first * ipw[i].first % mod1;
    hs.second = pref[j].second;
    if (i) hs.second = (hs.second - pref[i - 1].second + mod2) % mod2;
    hs.second = 1LL * hs.second * ipw[i].second % mod2;
    return hs;
}

// Concatenate two normalized hashes. The left length determines the power shift.
using Hash = pair<int,int>;
Hash merge_hash(Hash left, Hash right, int left_length) {
    return {(left.first + 1LL*pw[left_length].first*right.first) % mod1,
            (left.second + 1LL*pw[left_length].second*right.second) % mod2};
}

// Multiple texts can share the randomized power table. Indices are zero-based, inclusive.
struct PrefixHash {
    vector<Hash> pref;
    explicit PrefixHash(const string& s) : pref(s.size()+1) {
        prec();
        for (int i=0;i<(int)s.size();++i)
            pref[i+1] = merge_hash(pref[i], {(unsigned char)s[i], (unsigned char)s[i]}, i);
    }
    Hash get_hash(int l,int r) const {
        return {1LL*(pref[r+1].first-pref[l].first+mod1)*ipw[l].first%mod1,
                1LL*(pref[r+1].second-pref[l].second+mod2)*ipw[l].second%mod2};
    }
};

// Point edits, reversed substring hashes and palindrome tests. Indices here are one-based.
namespace editable {
using T = Hash;
T operator+(T a,T b) { return {(a.first+b.first)%mod1,(a.second+b.second)%mod2}; }
T operator*(T a,T b) { return {1LL*a.first*b.first%mod1,1LL*a.second*b.second%mod2}; }
T operator*(T a,int x) { return a*T{x,x}; }
struct MutableHash {
  int n;
  string s; // 1 - indexed
  vector<array<T, 2>> t; // (normal, rev) hash
  array<T, 2> merge(array<T, 2> l, array<T, 2> r) {
    l[0] = l[0] + r[0];
    l[1] = l[1] + r[1];
    return l;
  }
  void build(int node, int b, int e) {
    if (b == e) {
      t[node][0] = pw[b - 1] * (unsigned char)s[b];
      t[node][1] = pw[n - b] * (unsigned char)s[b];
      return;
    }
    int mid = (b + e) >> 1, l = node << 1, r = l | 1;
    build(l, b, mid);
    build(r, mid + 1, e);
    t[node] = merge(t[l], t[r]);
  }
  void upd(int node, int b, int e, int i, char x) {
    if (b > i || e < i) return;
    if (b == e && b == i) {
      t[node][0] = pw[b - 1] * (unsigned char)x;
      t[node][1] = pw[n - b] * (unsigned char)x;
      return;
    }
    int mid = (b + e) >> 1, l = node << 1, r = l | 1;
    upd(l, b, mid, i, x);
    upd(r, mid + 1, e, i, x);
    t[node] = merge(t[l], t[r]);
  }
  array<T, 2> query(int node, int b, int e, int i, int j) {
    if (b > j || e < i) return {T({0, 0}), T({0, 0})};
    if (b >= i && e <= j) return t[node];
    int mid = (b + e) >> 1, l = node << 1, r = l | 1;
    return merge(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
  }
  MutableHash() {}
  MutableHash(string _s) {
    n = _s.size();
    s = "." + _s;
    t.resize(4 * n + 1);
    prec();
    if (n) build(1, 1, n);
  }
  void upd(int i, char c) {
    upd(1, 1, n, i, c);
    s[i] = c;
  }
  T get_hash(int l, int r) { // 1 - indexed
    return query(1, 1, n, l, r)[0] * ipw[l - 1];
  }
  T rev_hash(int l, int r) { // 1 - indexed
    return query(1, 1, n, l, r)[1] * ipw[n - r];
  }
  T get_hash() {
    return n ? get_hash(1,n) : T{};
  }
  bool is_palindrome(int l, int r) {
    return get_hash(l, r) == rev_hash(l, r);
  }
};
}
