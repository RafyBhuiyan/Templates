const int MOD = 1e9+7;
const int MX = 1e6 + 1;
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
    int binpow(int a, int p)
    {
        int ans = 1;
        while (p)
        {
            if (p % 2)
            {
                ans = (ans * a) % mod;
            }
            p /= 2;
            a = (a * a) % mod;
        }
        return ans;
    }
    int gun(int a, int b)
    {
        return ((a % mod) * (b % mod)) % mod;
    }
    int jog(int a, int b)
    {
        return (a + b) % mod;
    }
    int biyog(int a, int b)
    {
        return (a%mod - b%mod + mod) % mod;
    }
    int bininv(int a)
    {
        return binpow(a, mod - 2);
    }
    int vag(int a, int b)
    {
        return gun(a, bininv(b));
    }
} comb(MX, MOD);
