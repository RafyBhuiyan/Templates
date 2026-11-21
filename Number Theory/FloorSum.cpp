#include <bits/stdc++.h>
using namespace std;

using ll = long long;
//sum of floor((a * i + b) / m) for 0 <= i <= n
ll fsum(ll a, ll b, ll m, ll n){
	if(n < 0)return 0;
	if(a == 0)return b / m * (n + 1);
	if(a >= m || b >= m)return a / m * (n * (n + 1) / 2) + b / m * (n + 1) + fsum(a % m, b % m, m, n);
	ll t = (a * n + b) / m;
	return n * t - fsum(m, m - b - 1, a, t - 1);
}

// Sum of (a + i*d) mod m for i in [0,n). m > 0, n >= 0; intermediate products must fit.
ll mod_sum(ll a, ll d, ll m, ll n) {
    a = (a % m + m) % m;
    d = (d % m + m) % m;
    return n * a + d * (n * (n - 1) / 2) - m * fsum(d, a, m, n - 1);
}
