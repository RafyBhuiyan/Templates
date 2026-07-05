#include<bits/stdc++.h>
#define int long long int
#define no "No"
#define yes "Yes"
#define decimal(n) cout<<fixed<<setprecision(n);
#define For(i,n) for(ll i=0;i<n;i++)
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
void io()
{
    freopen("bujhina.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
}
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;
typedef tree<ll,null_type,less_equal<ll>,rb_tree_tag,tree_order_statistics_node_update>multi_ordered_set;
*/

void show(int x) {cerr << x;}
// void show(long long x) {cerr << x;}
void show(double x) {cerr << x;}
void show(char x) {cerr << '\'' << x << '\'';}
void show(const string &x) {cerr << '\"' << x << '\"';}
void show(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void show(pair<T, V> x) { cerr << '{'; show(x.first); cerr << ", "; show(x.second); cerr << '}'; }
template<typename T>
void show(T x) {int f = 0; cerr << "{"; for (auto &i : x) cerr << (f++ ? ", " : ""), show(i); cerr << "}";}
void debug_out(string s) {
    s.clear();
    cerr << s << '\n';
}
template <typename T, typename... V>
void debug_out(string s, T t, V... v) {
    s.erase(remove(s.begin(), s.end(), ' '), s.end());
    cerr << "        "; // 8 spaces
    cerr << s.substr(0, s.find(','));
    s = s.substr(s.find(',') + 1);
    cerr << " = ";
    show(t);
    cerr << endl;
    if (sizeof...(v)) debug_out(s, v...);
}
#define dbg(x...) cerr << "LINE: " << __LINE__ << endl; debug_out(#x, x); cerr << endl;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int gen_random(int l, int r) {return uniform_int_distribution<int>(l, r)(rng);}
void TLE()
{
    clock_t shuru = clock(); // call it in the main code
    (clock() - shuru) * 1.0 / CLOCKS_PER_SEC < 3.5;
}
const int mod = 1e9 + 7;
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
    return (a - b + mod) % mod;
}
int inv(int a)
{
    return binpow(a,mod-2);
}
int vag(int a,int b)
{
    return gun(a,inv(b));
}
int ask(int l, int r)
{
    int x;
    cout << "? " << l << " " << r << endl;
    cin >> x;
    return x;
}

void solve()
{
}
int32_t main()
{
    fastio
    // io();
    int test = 1;
    cin >> test;
    while (test--)
    {
        // cout << "Case " << i + 1 << ": ";
        solve();
    }
    return 0;
}
