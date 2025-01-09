#include<bits/stdc++.h>
#include <algorithm>
#include <numeric>
#define ll long long int
#define For(i,n) for(ll i=0;i<n;i++)
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

vector<ll>graph[200001];
int totalchild[200001];
int nodes,edges,u,v,x,maxx;
vector<ll>centroids;
void centrd(int curr,int par)
{
    maxx = 0;
    for(auto child:graph[curr])
    {
        if(child==par)
            continue;
        centrd(child,curr);
        totalchild[curr]+=totalchild[child];
        maxx = max(maxx,totalchild[child]);
    }
    x = nodes - 1 - totalchild[curr];
    if(x*2<=nodes && maxx*2<=nodes) centroids.push_back(curr);
    totalchild[curr]++;
}
void solve()
{
    cin>>nodes;
    edges = nodes-1;
    For(i,edges)
    {
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    centrd(1,0);
    cout<<centroids[0]<<endl;
}
int main()
{
    fastio
    //io();
    ll test=1;
    //cin>>test;
    For(i,test)
    {
        //cout<<"Case "<<i+1<<": "<<endl;
        solve();
    }
    return 0;
}
