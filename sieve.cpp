const ll N = 1e6 + 1;
int spf[N], vis[N], maxx[N];
vector<int>vp;
void sieve()
{
    spf[1] = 1;
    spf[2] = 2;
    for (int i = 4; i < N; i += 2) spf[i] = 2;
    for (ll i = 3; i < N; i += 2)
    {
        if (vis[i]) continue;
        vp.push_back(i);
        spf[i] = i;
        for (ll j = i * i; j < N; j += 2 * i)
        {
            if (!vis[j])
            {
                vis[j] = 1;
                spf[j] = i;
            }
        }
    }
}
vector<ll> pfactor(ll n)
{
    vector<ll>v;
    while (spf[n] != 1)
    {
        v.push_back(spf[n]);
        n /= spf[n];
    }
    return v;
}
