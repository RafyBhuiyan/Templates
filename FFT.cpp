typedef double ld;
typedef complex <ld> cplx;

const ld PI = acosl(-1);
const int MOD = 1e9 + 7;
const int N = (1 << 20) + 69;

int rev[N];
cplx w[N];

void prepare (int n)
{
    int sz = __builtin_ctz(n);
    for (int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (sz - 1));
    w[0] = 0, w[1] = 1, sz = 1;
    while (1 << sz < n)
    {
        ld ang = 2 * PI / (1 << (sz + 1));
        cplx w_n = cplx(cosl(ang), sinl(ang));
        for (int i = 1 << (sz - 1); i < (1 << sz); ++i)
        {
            w[i << 1] = w[i], w[i << 1 | 1] = w[i] * w_n;
        }
        ++sz;
    }
}

void fft (cplx *a, int n)
{
    for (int i = 1; i < n - 1; ++i)
    {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int h = 1; h < n; h <<= 1)
    {
        for (int s = 0; s < n; s += h << 1)
        {
            for (int i = 0; i < h; ++i)
            {
                cplx &u = a[s + i], &v = a[s + i + h], t = v * w[h + i];
                v = u - t, u = u + t;
            }
        }
    }
}

static cplx f[N];

vector <int> multiply (vector <int> a, vector <int> b)
{
    int n = a.size(), m = b.size();
    int sz = n + m - 1;
    while (sz & (sz - 1)) sz = (sz | (sz - 1)) + 1;
    prepare(sz);
    for (int i = 0; i < sz; ++i) f[i] = cplx(i < n ? a[i] : 0, i < m ? b[i] : 0);
    fft(f, sz);
    for (int i = 0; i <= (sz >> 1); ++i)
    {
        int j = (sz - i) & (sz - 1);
        cplx x = (f[i] * f[i] - conj(f[j] * f[j])) * cplx(0, -0.25);
        f[j] = x, f[i] = conj(x);
    }
    fft(f, sz);
    vector <int> c(n + m - 1);
    for(int i = 0; i < n + m - 1; ++i) c[i] = min((f[i].real() / sz + 0.5),1.0);
    return c;
}


//fast one

using cd = complex<double>;
void fft(vector<cd> &a, bool invert)
{
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1)
    {
        double ang = 2 * acos(-1) / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len)
        {
            cd w(1);
            for (int j = 0; j < (len >> 1); j++)
            {
                cd u = a[i + j], v = a[i + j + (len >> 1)] * w;
                a[i + j] = u + v;
                a[i + j + (len >> 1)] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert)
    {
        for (cd & x : a)
            x /= n;
    }
}

vector<ll> multiply(vector<ll> &a, vector<ll> &b)
{
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    ll n = 1;
    while(n < a.size() + b.size())n <<= 1;
    fa.resize(n), fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for(int i = 0; i < n; i++)fa[i] *= fb[i];
    fft(fa, true);
    vector<ll> res(n);
    for(int i = 0; i < n; i++)
    {
        res[i] = round(fa[i].real());
        if(res[i]) res[i] = 1;
    }
    return res;
}

