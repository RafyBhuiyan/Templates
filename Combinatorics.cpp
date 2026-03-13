const int MOD = 998244353;
const int MX = 5000001;
struct Combinatorics
{
    int n, mod;
    vector<int> _fac, _inv, _ifac;
    Combinatorics(int n, int mod) : n(n), mod(mod), _fac(n + 1),_inv(n + 1), _ifac(n + 1)
    {
        for (int i = 0; i <= 1; ++i) _fac[i] = _inv[i] = _ifac[i] = 1;
        for (int i = 2; i <= n; ++i) _fac[i] = (_fac[i - 1] * i)% mod;
        for (int i = 2; i <= n; ++i) _inv[i] = mod - ((mod / i *_inv[mod % i]) % mod);
        for (int i = 2; i <= n; ++i) _ifac[i] = (_ifac[i - 1] * _inv[i]) % mod;
    }
    int fac(int n)
    {
        return _fac[n];
    }
    int ifac(int n)
    {
        return _ifac[n];
    }
    int inv(int n)
    {
        return _inv[n];
    }
    int ncr(int n, int r)
    {
        if (r > n) return 0;
        int ans = fac(n);
        ans = (ans * ifac(r)) % mod;
        ans = (ans * ifac(n - r)) % mod;
        return ans;
    }
    int npr(int n, int r)
    {
        if (r > n) return 0;
        int ans = fac(n);
        ans = (ans * ifac(n - r)) % mod;
        return ans;
    }
} comb(MX, MOD);
