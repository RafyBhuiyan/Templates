#include<bits/stdc++.h>
#include <algorithm>
#include <numeric>
#define ll long long int
#define For(i,n) for(ll i=0;i<n;i++)
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

vector<ll>graph[200001];
int totalchild[200001];
int nodes,edges,u,v,x;
vector<ll>centroids;
void centrd(int curr,int par)
{
    int maxx = 0;
    totalchild[curr] = 0;
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
// The decomposition reuses the same input tree. cenpar and dep describe the centroid tree.
namespace decomposition {
constexpr int N = 200001;
int sz[N];
int tot, done[N], cenpar[N], level[N];
void calc_sz(int u, int p) {
  tot ++;
  sz[u] = 1;
  for (auto v : graph[u]) {
    if(v == p || done[v]) continue;
    calc_sz(v, u);
    sz[u] += sz[v];
  }
}
int find_cen(int u, int p) {
  for (auto v : graph[u]) {
    if(v == p || done[v]) continue;
    else if(sz[v] > tot / 2) return find_cen(v, u);
  }
  return u;
}
void decompose(int u, int pre) {
  tot = 0;
  calc_sz(u, pre);
  int cen = find_cen(u, pre);
  cenpar[cen] = pre;
  level[cen] = pre ? level[pre]+1 : 0;
  done[cen] = 1;
  for(auto v : graph[cen]) {
    if(v == pre || done[v]) continue;
    decompose(v, cen);
  }
}
int dep[N];
void dfs(int u, int p = 0) {
  for(auto v : graph[u]) {
    if(v == p) continue;
    dep[v] = dep[u] + 1;
    dfs(v, u);
  }
}

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
    centroids.clear();
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
