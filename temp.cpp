#include<bits/stdc++.h>
#define ll long long int
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
inline ll gen_random(ll l, ll r)
{
    return uniform_int_distribution<ll>(l, r)(rng);
}
void TLE()
{
    clock_t shuru = clock(); // call it in the main code
    (clock() - shuru) * 1.0 / CLOCKS_PER_SEC < 3.5;
}

ll ask(ll l, ll r)
{
    ll x;
    cout << "? " << l << " " << r << endl;
    cin >> x;
    return x;
}

void solve(int test)
{
}
int main()
{
    fastio
    // io();
    ll test = 1;
    cin >> test;
    For(i, test)
    {
        // cout << "Case #" << i + 1 << ": ";
        solve(i);
    }
    return 0;
}
    