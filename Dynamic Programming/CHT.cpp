#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 3e5 + 9;
const int mod = 1e9 + 7;

struct CHT {
  vector<ll> m, b;
  int ptr = 0;
  bool bad(int l1, int l2, int l3) {
    return ((__int128)b[l3] - b[l1]) * (m[l1] - m[l2])  <= ((__int128)b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query min),(slope inc+query max)
    //return ((__int128)b[l3] - b[l1]) * (m[l1] - m[l2])  > ((__int128)b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query max), (slope inc+query min)
  }
  void add(ll _m, ll _b) {
    if (!m.empty() && m.back() == _m) {
      if (b.back() <= _b) return;
      m.pop_back(); b.pop_back();
    }
    m.push_back(_m);
    b.push_back(_b);
    int s = m.size();
    while(s >= 3 && bad(s - 3, s - 2, s - 1)) {
      s--;
      m.erase(m.end() - 2);
      b.erase(b.end() - 2);
    }
  }
  ll f(int i, ll x) {
    return m[i] * x + b[i];
  }

  //(slope dec+query min), (slope inc+query max) -> x increasing
  //(slope dec+query max), (slope inc+query min) -> x decreasing
  ll query(ll x) {
    if(ptr >= m.size()) ptr = m.size() - 1;
    while(ptr < m.size() - 1 && f(ptr + 1, x) < f(ptr, x)) ptr++;
    return f(ptr, x);
  }

  ll bs(int l, int r, ll x) {
    int mid = (l + r) / 2;
    if(mid + 1 < m.size() && f(mid + 1, x) < f(mid, x)) return bs(mid + 1, r, x); // > for max
    if(mid - 1 >= 0 && f(mid - 1, x) < f(mid, x)) return bs(l, mid - 1, x); // > for max
    return f(mid, x);
  }
};
void cht_example()
{
    ll n,ans=0;
    cin>>n;
    vector<ll>ra(n),sa(n),dp(n);
    for (int i = 0; i < n; ++i) cin>>ra[i];
    for (int i = 0; i < n; ++i) cin>>sa[i];
    CHT cht;
    dp[0] = 0;
    cht.add(sa[0],0);
    for(int i=1;i<n;i++)
    {
        dp[i] = cht.query(ra[i]);
        cht.add(sa[i],dp[i]);
    }
    cout<<dp[n-1]<<endl;
}

// Arbitrary insertion order, maximum line value in logarithmic time.
namespace arbitrary_slopes {
constexpr ll inf = LLONG_MIN; // reserved intercept for queries
struct line {
  ll m, b;
  mutable function<const line*() > succ;
  bool operator < (const line& rhs) const {
    if (rhs.b != inf) return m < rhs.m;
    const line* s = succ();
    if (!s) return 0;
    ll x = rhs.m;
    return (__int128)b - s->b < ((__int128)s->m - m) * x;
  }
};
struct CHT : public multiset<line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y -> m == z -> m && y -> b <= z -> b;
    }
    auto x = prev(y);
    if (z == end()) return y -> m == x -> m && y -> b <= x -> b;
    return ((__int128)x->b-y->b) * (z -> m - y -> m) >= ((__int128)y->b-z->b) * (y -> m - x -> m);
  }
  void add(ll m, ll b) {
    auto y = insert({ m, b });
    y->succ = [this,y] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) {
      erase(y);
      return;
    }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound((line) {
      x, inf
    });
    return l.m * x + l.b;
  }
};

}
