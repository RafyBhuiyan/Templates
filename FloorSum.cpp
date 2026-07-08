//sum of floor((a * i + b) / m) for 0 <= i <= n
ll fsum(ll a, ll b, ll m, ll n){
	if(n < 0)return 0;
	if(a == 0)return b / m * (n + 1);
	if(a >= m || b >= m)return a / m * (n * (n + 1) / 2) + b / m * (n + 1) + fsum(a % m, b % m, m, n);
	ll t = (a * n + b) / m;
	return n * t - fsum(m, m - b - 1, a, t - 1);
}
