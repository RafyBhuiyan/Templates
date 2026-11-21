#include <bits/stdc++.h>
using namespace std;

// For a prime modulus and a precomputation limit smaller than the modulus.
const int MOD = 1e9+7;
const int MX = 1e6 + 1;
struct Combinatorics
{
    int n, mod;
    vector<int> _fac, _inv, _ifac;
    Combinatorics(int n, int mod) : n(n), mod(mod), _fac(n + 1),_inv(n + 1), _ifac(n + 1)
    {
        for (int i = 0; i <= min<int>(n, 1); ++i) _fac[i] = _inv[i] = _ifac[i] = 1;
        for (int i = 2; i <= n; ++i) _fac[i] = (1LL * _fac[i - 1] * i)% mod;
        for (int i = 2; i <= n; ++i) _inv[i] = mod - ((1LL * (mod / i) *_inv[mod % i]) % mod);
        for (int i = 2; i <= n; ++i) _ifac[i] = (1LL * _ifac[i - 1] * _inv[i]) % mod;
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
        if (r < 0 || r > n) return 0;
        int ans = fac(n);
        ans = (1LL * ans * ifac(r)) % mod;
        ans = (1LL * ans * ifac(n - r)) % mod;
        return ans;
    }
    // For n beyond the table, with min(r,n-r) < mod and prime mod.
    int ncr_small_r(long long n, long long r) {
        if (r < 0 || r > n) return 0;
        r = min(r, n - r);
        long long top = 1, bottom = 1;
        for (long long i = 1; i <= r; ++i) {
            top = top * ((n - i + 1) % mod) % mod;
            bottom = bottom * i % mod;
        }
        return top * bininv(bottom) % mod;
    }
    // Lucas theorem for a small prime; construct the table through mod - 1.
    int lucas(long long n, long long r) {
        assert(this->n >= mod - 1);
        if (r < 0 || r > n) return 0;
        long long ans = 1;
        while (r) {
            ans = ans * ncr(n % mod, r % mod) % mod;
            n /= mod;
            r /= mod;
        }
        return ans;
    }
    // Exact coefficient when the result fits in a signed 64-bit integer.
    static long long ncr_exact(long long n, long long r) {
        if (r < 0 || r > n) return 0;
        r = min(r, n - r);
        long long result = 1;
        for (long long i = 1; i <= r; ++i) {
            __int128 next = (__int128)result * (n - r + i) / i;
            if (next > LLONG_MAX) throw overflow_error("binomial coefficient");
            result = (long long)next;
        }
        return result;
    }
    int npr(int n, int r)
    {
        if (r < 0 || r > n) return 0;
        int ans = fac(n);
        ans = (1LL * ans * ifac(n - r)) % mod;
        return ans;
    }
    int binpow(int a, int p)
    {
        int ans = 1;
        while (p)
        {
            if (p % 2)
            {
                ans = (1LL * ans * a) % mod;
            }
            p /= 2;
            a = (1LL * a * a) % mod;
        }
        return ans;
    }
    int gun(int a, int b)
    {
        return (1LL * (a % mod) * (b % mod)) % mod;
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
