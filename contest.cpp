#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
// Optional snippet include, before the int macro: #include "Strings/Suffix_Array.cpp"
using namespace std;
using namespace __gnu_pbds;
#define int long long int
#define no "NO"
#define yes "YES"
#define For(i,n) for(int i = 0;i<n;i++)
#define decimal(n) cout<<fixed<<setprecision(n);
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using ll = long long;
template<class Key, class Compare = less<Key>>
using ordered_tree = tree<Key, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_set = ordered_tree<int>;
using ordered_rset = ordered_tree<int, greater<int>>;
template<class K, class V>
using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

// Duplicate keys carry a unique insertion ID. find_by_order(k) is zero-based.
template<class Compare>
struct OrderedMultiset {
    using Key = pair<int, int>;
    ordered_tree<Key, Compare> data;
    int next_id = 0;
    void insert(int x) { data.insert({x, next_id++}); }
    auto lower_bound(int x) const {
        return data.lower_bound({x, Compare{}({x, 0}, {x, 1}) ? -1 : LLONG_MAX});
    }
    auto upper_bound(int x) const {
        return data.upper_bound({x, Compare{}({x, 0}, {x, 1}) ? LLONG_MAX : -1});
    }
    auto find_by_order(size_t k) const { return data.find_by_order(k); }
    int order_of_key(int x) const {
        return data.order_of_key({x, Compare{}({x, 0}, {x, 1}) ? -1 : LLONG_MAX});
    }
    bool erase(int x) {
        auto it = lower_bound(x);
        if (it == data.end() || it->first != x) return false;
        data.erase(it);
        return true;
    }
    auto size() const { return data.size(); }
    auto end() const { return data.end(); }
};
using ordered_multiset = OrderedMultiset<less<pair<int, int>>>;
using ordered_rmultiset = OrderedMultiset<greater<pair<int, int>>>;

// shuffle(a.begin(), a.end(), rng) shuffles a range. Tie-breaking keys can use std::pair.
string decimal128(__int128 x) {
    bool neg=x<0;
    unsigned __int128 u=neg ? -(unsigned __int128)x : (unsigned __int128)x;
    string digits;
    do { digits.push_back(char('0'+u%10)); u/=10; } while(u);
    if(neg) digits.push_back('-');
    reverse(digits.begin(),digits.end());
    return digits;
}
void io(const char* input = "input.txt", const char* output = "output.txt")
{
    freopen(input, "r", stdin);
    freopen(output, "w", stdout);
}

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
// Capture start=clock() in solve(), then call within_time(start) inside a timed loop.
bool within_time(clock_t start, double seconds=3.5) {
    return double(clock()-start)/CLOCKS_PER_SEC < seconds;
}
const int mod = 1e9 + 7;
int binpow(int a, int p, int modulus = mod)
{
    int ans = 1 % modulus;
    a %= modulus;
    if (a < 0) a += modulus;
    while (p)
    {
        if (p % 2)
        {
            ans = (__int128)ans * a % modulus;
        }
        p /= 2;
        a = (__int128)a * a % modulus;
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

void solve(int tst)
{
}
int32_t main()
{
    fastio
    // io();
    int test = 1;
    // cin >> test;
    For(i, test)
    {
        // cout << "Case " << i + 1 << ": ";
        solve(i + 1);
    }
    return 0;
}
