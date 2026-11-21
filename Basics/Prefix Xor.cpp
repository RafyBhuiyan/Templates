#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 9;
int pref_xor[N];
int a[N];
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, q; cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++) {
    pref_xor[i] = pref_xor[i - 1] ^ a[i];
  }
  while (q--) {
    int l, r; cin >> l >> r;
    cout << (pref_xor[r] ^ pref_xor[l - 1]) << '\n';
  }
  return 0;
}
// https://cses.fi/problemset/task/1646/

long long Xor(long long n){
    if(n%4==0)return n;
    if(n%4==1)return 1;
    if(n%4==2)return n+1;
    return 0;
}
long long XorTill(long long l,long long r){
    if(l==0)return Xor(r);
    else return Xor(r) xor Xor(l-1);
}
