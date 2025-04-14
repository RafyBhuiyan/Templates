#include<bits/stdc++.h>
#define ll long long int
#define no "NO"
#define yes "YES"
#define decimal(n) cout<<fixed<<setprecision(n);
#define For(i,n) for(ll i=0;i<n;i++)
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
void io()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
}
class SegTree
{
public:
    ll n;
    vector<ll>tree,arr;
    SegTree(vector<ll>&v)
    {
        n = v.size();
        arr = v;
        tree.assign(4*n,0);
        build(1,0,n-1);
    }
    SegTree(ll _n)
    {
        tree.assign(4*_n,0);
        n = _n;
    }
    void update(ll ind,ll val)
    {
        update(1,0,n-1,ind,val);
    }
    ll query(ll l,ll r)
    {
        return query(1,0,n-1,l,r);
    }
private:
    ll merge(ll a,ll b)
    {
        return (a+b);
    }
    void build(ll node,ll start,ll end)
    {
        if(start==end)tree[node] = arr[start];
        else
        {
            ll mid = (start+end)/2;
            build(2*node,start,mid);
            build(2*node+1,mid+1,end);
            tree[node] = merge(tree[2*node],tree[2*node+1]);
        }
    }
    void update(ll node,ll start,ll end,ll ind,ll val)
    {
        if(ind<start or ind>end)return;
        if(start==end)tree[node] = val;
        else
        {
            ll mid = (start+end)/2;
            if(start<=ind and ind<=mid)update(2*node,start,mid,ind,val);
            else update(2*node+1,mid+1,end,ind,val);
            tree[node] = merge(tree[2*node],tree[2*node+1]);
        }
    }
    ll query(ll node,ll start,ll end,ll l,ll r)
    {

        if(end<l or start>r)return 0;
        if(start==end)return tree[node];
        else if(l<=start and end<=r)return tree[node];
        else
        {
            ll mid = (start+end)/2;
            ll left = query(2*node,start,mid,l,r);
            ll right = query(2*node+1,mid+1,end,l,r);
            return merge(left,right);
        }
    }
};


void solve()
{

}
int main()
{
    fastio
    //io();
    ll test=1;
    //cin>>test;
    For(i,test)
    {
        //cout<<"Case "<<i+1<<": ";
        solve();
    }
    return 0;
}
