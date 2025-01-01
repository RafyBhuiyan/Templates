#include<bits/stdc++.h>
#define ll long long int
#define For(i,n) for(ll i=0;i<n;i++)
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;


const int N = 3e5 + 9;
const int mod = 1e9 + 7;

struct CHT {
  vector<ll> m, b;
  int ptr = 0;

  bool bad(int l1, int l2, int l3) {
    return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  <= 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query min),(slope inc+query max)
    //return 1.0 * (b[l3] - b[l1]) * (m[l1] - m[l2])  > 1.0 * (b[l2] - b[l1]) * (m[l1] - m[l3]); //(slope dec+query max), (slope inc+query min)
  }

  void add(ll _m, ll _b) {
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
void solve(ll curr)
{
    ll n,ans=0;
    cin>>n;
    vector<ll>ra(n),sa(n),dp(n);
    For(i,n) cin>>ra[i];
    For(i,n) cin>>sa[i];
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
int main()
{
    fastio
    //io();
    ll test=1;
    //cin>>test;
    For(i,test)
    {
        //cout<<"Case "<<i+1<<": ";
        solve(i+1);
    }
    return 0;
}


