#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;
vector<int> g[N];
bool vis[N];
vector<int> ord;
void dfs(int u) {
  vis[u] = true;
  for (auto v: g[u]) {
    if (!vis[v]) {
      dfs(v);
    }
  }
  ord.push_back(u);
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m; cin >> n >> m;
  while (m--) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i);
    }
  }
  reverse(ord.begin(), ord.end());

  // check is feasible
  vector<int> pos(n + 1);
  for (int i = 0; i < (int) ord.size(); i++) {
    pos[ord[i]] = i;
  }
  for (int u = 1; u <= n; u++) {
    for (auto v: g[u]) {
      // We need to consider self loops too!
      if (pos[u] >= pos[v]) { 
        cout << "IMPOSSIBLE\n";
        return 0;
      }
    }
  }

  // print the order
  for (auto u: ord) cout << u << ' ';
  cout << '\n';
  return 0;
}
// https://cses.fi/problemset/task/1679

// Kahn's indegree algorithm; an empty optional means a cycle. Vertices are zero-based.
optional<vector<int>> kahn_order(const vector<vector<int>>& graph) {
    vector<int> indegree(graph.size()),order;
    for(const auto& row:graph) for(int v:row) ++indegree[v];
    queue<int> ready;
    for(int i=0;i<(int)graph.size();++i) if(!indegree[i]) ready.push(i);
    while(!ready.empty()) {
        int u=ready.front(); ready.pop(); order.push_back(u);
        for(int v:graph[u]) if(!--indegree[v]) ready.push(v);
    }
    if(order.size()!=graph.size()) return nullopt;
    return order;
}
