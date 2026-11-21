#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, LG = 18;

vector<pair<int,long long>> g[N];
long long minw[N][LG+1],maxw[N][LG+1];
int enter[N], leave[N], timer;
int par[N][LG + 1], dep[N], sz[N];
void dfs(int u,int p=0,long long weight=0) {
    enter[u]=timer++;
    minw[u][0]=p ? weight : LLONG_MAX;
    maxw[u][0]=p ? weight : LLONG_MIN;
  par[u][0] = p;
  dep[u] = dep[p] + 1;
  sz[u] = 1;
  for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
  for(int i=1;i<=LG;++i) {
    int a=par[u][i-1];
    minw[u][i]=a ? min(minw[u][i-1],minw[a][i-1]) : minw[u][i-1];
    maxw[u][i]=a ? max(maxw[u][i-1],maxw[a][i-1]) : maxw[u][i-1];
  }
  for(auto [v,w]:g[u]) if(v!=p) {
    dfs(v,u,w);
    sz[u] += sz[v];
  }
  leave[u]=timer;
}
int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
  if (u == v) return u;
  for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
  return par[u][0];
}
int kth(int u, int k) {
  assert(k >= 0);
  for (int i = 0; i <= LG; i++) if (k & (1 << i)) u = par[u][i];
  return u;
}
int dist(int u, int v) {
  int l = lca(u, v);
  return dep[u] + dep[v] - (dep[l] << 1);
}
//kth node from u to v, 0th node is u
int go(int u, int v, int k) {
  int l = lca(u, v);
  int d = dep[u] + dep[v] - (dep[l] << 1);
  assert(k <= d);
  if (dep[l] + k <= dep[u]) return kth(u, k);
  k -= dep[u] - dep[l];
  return kth(v, dep[v] - dep[l] - k);
}
// Edge weights along u..v. Empty paths have no extrema.
optional<pair<long long,long long>> path_minmax(int u,int v) {
    int a=lca(u,v);
    if(u==v) return nullopt;
    long long lo=LLONG_MAX, hi=LLONG_MIN;
    for(int x : {u,v}) {
        int delta=dep[x]-dep[a];
        for(int i=LG;i>=0;--i) if((delta>>i)&1) {
            lo=min(lo,minw[x][i]); hi=max(hi,maxw[x][i]);
            x=par[x][i];
        }
    }
    return pair{lo,hi};
}
int32_t main() {
  int n; cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    g[u].emplace_back(v,1);
    g[v].emplace_back(u,1);
  }
  dfs(1);
  int q; cin >> q;
  while (q--) {
    int u, v; cin >> u >> v;
    cout << dist(u, v) << '\n';
  }
  return 0;
}
// Euler-tour RMQ for constant-time LCA queries.
namespace euler_rmq {
template <class T>
struct RMQ { // 0-based
  vector<vector<T>> rmq;
  T kInf = numeric_limits<T>::max();
  void build(const vector<T>& V) {
    int n = V.size(), on = 1, dep = 1;
    while (on < n) on *= 2, ++dep;
    rmq.assign(dep, V);
 
    for (int i = 0; i < dep - 1; ++i)
      for (int j = 0; j < n; ++j) {
        rmq[i + 1][j] = min(rmq[i][j], rmq[i][min(n - 1, j + (1 << i))]);
      }
  }
  T query(int a, int b) { // [a, b)
    if (b <= a) return kInf;
    int dep = 31 - __builtin_clz(b - a); // log(b - a)
    return min(rmq[dep][a], rmq[dep][b - (1 << dep)]);
  }
};

struct LCA { // 0-based
  vector<int> enter, depth, exxit;
  vector<vector<int>> G;
  vector<pair<int, int>> linear;
  RMQ<pair<int, int>> rmq;
  int timer = 0;
  LCA() {} 
  LCA(int n) : enter(n, -1), exxit(n, -1), depth(n), G(n), linear(2 * n) {}
  void dfs(int node, int dep) {
    linear[timer] = {dep, node};
    enter[node] = timer++;
    depth[node] = dep;
    for (auto vec : G[node])
    if (enter[vec] == -1) {
      dfs(vec, dep + 1);
      linear[timer++] = {dep, node};
    }
    exxit[node] = timer;
  }
  void add_edge(int a, int b) {
    G[a].push_back(b);
    G[b].push_back(a);
  }
  void build(int root) {
    dfs(root, 0);
    rmq.build(linear);
  }
  int query(int a, int b) {
    a = enter[a], b = enter[b];
    return rmq.query(min(a, b), max(a, b) + 1).second;
  }
  int dist(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[query(a, b)];
  }
};
 

}
