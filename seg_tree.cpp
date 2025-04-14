#include<bits/stdc++.h>
#define ll long long int
#define br <<"\n"
#define no "NO"
#define yes "YES"
#define decimal(n) cout<<fixed<<setprecision(n);
#define For(i,n) for(ll i=0;i<n;i++)
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

class SegTree
{
public:
    int n;
    vector<int>tree,arr;
    SegTree(vector<int>&v)
    {
        n = v.size();
        arr = v;
        tree.assign(4*n,0);
        build(1,0,n-1);
    }
    void update(int ind,int val)
    {
        update(1,0,n-1,ind,val);
    }
    int query(int l,int r)
    {
        return query(1,0,n-1,l,r);
    }
private:
    int merge(int a,int b)
    {
        return (a+b);
    }
    void build(int node,int start,int end)
    {
        if(start==end)tree[node] = arr[start];
        else
        {
            int mid = (start+end)/2;
            build(2*node,start,mid);
            build(2*node+1,mid+1,end);
            tree[node] = merge(tree[2*node],tree[2*node+1]);
        }
    }
    void update(int node,int start,int end,int ind,int val)
    {
        if(ind<start or ind>end)return;
        if(start==end)tree[node] = val;
        else
        {
            int mid = (start+end)/2;
            if(start<=ind and ind<=mid)update(2*node,start,mid,ind,val);
            else update(2*node+1,mid+1,end,ind,val);
            tree[node] = merge(tree[2*node],tree[2*node+1]);
        }
    }
    int query(int node,int start,int end,int l,int r)
    {

        if(end<l or start>r)return 0;
        if(start==end)return tree[node];
        else if(l<=start and end<=r)return tree[node];
        else
        {
            int mid = (start+end)/2;
            int left = query(2*node,start,mid,l,r);
            int right = query(2*node+1,mid+1,end,l,r);
            return merge(left,right);
        }
    }
};


void solve()
{
    int n;
    cin>>n;
    vector<int>ra(n);
    SegTree sg = SegTree(ra);
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
