#include<bits/stdc++.h>
using namespace std;

const int B = 20;
int a[1 << B], f[1 << B], g[1 << B];
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    f[a[i]]++;
    g[a[i]]++;
  }

  // sum over subsets
  for (int i = 0; i < B; i++) {
    for (int mask = 0; mask < (1 << B); mask++) {
      if ((mask & (1 << i)) != 0) {
        f[mask] += f[mask ^ (1 << i)];
      }
    }
  }

  // sum over supersets
  for (int i = 0; i < B; i++) {
    for (int mask = (1 << B) - 1 ; mask >= 0 ; mask--) {
      if ((mask & (1 << i)) == 0) g[mask] += g[mask ^ (1 << i)] ;
    }
  }
  
  for (int i = 1; i <= n; i++) {
    cout << f[a[i]] << ' ' << g[a[i]] << ' ' << n - f[(1 << B) - 1 - a[i]] << '\n';
  }
  return 0;
}
// https://cses.fi/problemset/task/1654

// Subset/superset zeta transform, or its inverse when inverse=true.
template<class T>
void sos_transform(vector<T>& a, bool supersets=false, bool inverse=false) {
    size_t n=a.size();
    assert(n && !(n & (n-1)));
    for(size_t bit=1;bit<n;bit<<=1) for(size_t m=0;m<n;++m) if(m&bit) {
        size_t dest=supersets ? m^bit : m, src=supersets ? m : m^bit;
        if(inverse) a[dest]-=a[src]; else a[dest]+=a[src];
    }
}
// Enumerate nonempty submasks with: for(int sub=mask; sub; sub=(sub-1)&mask).
