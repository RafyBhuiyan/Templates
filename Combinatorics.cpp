const ll MOD = 1e9+7;
const ll MX = 1e6;
struct Combinatorics
{
    ll n,mod;
    vector<ll> _fac, _inv, _ifac;
    Combinatorics(ll n, ll mod) : n(n), mod(mod),_fac(n+1), _inv(n+1), _ifac(n+1)
    {
        for (ll i = 0; i <= 1; ++i) _fac[i] = _inv[i] = _ifac[i] = 1;
        for (ll i = 2; i <= n; ++i) _fac[i] = (_fac[i-1] * i) % mod;
        for (ll i = 2; i <= n; ++i) _inv[i] = mod - ((mod/i * _inv[mod % i]) % mod);
        for (ll i = 2; i <= n; ++i) _ifac[i] = (_ifac[i-1] * _inv[i]) % mod;
    }
    ll fac(ll n)
    {
        return _fac[n];
    }
    ll ifac(ll n)
    {
        return _ifac[n];
    }
    ll inv(ll n)
    {
        return _inv[n];
    }
    ll ncr(ll n, ll r)
    {
        if (r > n) return 0;
        ll ans = fac(n);
        ans = (ans * ifac(r)) % mod;
        ans = (ans * ifac(n-r)) % mod;
        return ans;
    }
} comb(MX, MOD);
