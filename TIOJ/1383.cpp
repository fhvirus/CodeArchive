#include <bits/stdc++.h>
using namespace std;

void answer(bool b) { cout << (b ? "YES\n" : "NO\n"); exit(0); }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<int> rank(n);
  vector<vector<int>> adj(n);
  set<pair<int, int>> es;
  for (int &i : rank) cin >> i;

  for (int u, v, i = 0; i < m; ++i) {
    cin >> u >> v; --u, --v;
    if (u > v) swap(u, v);
    if (not es.insert({u, v}).second) continue;
    adj[u].push_back(v);
    adj[v].push_back(u);
    if (max(size(adj[u]), size(adj[v])) > 3) answer(false);
  }
  if ((int)size(es) != n - 1) answer(false);
  
  const auto dfs = [&](const auto& self, int u, int p, int lb, int rb) -> int {
    if (lb > rank[u] or rank[u] >= rb) return -1;
    int s = 1, lt = 0;
    for (int v : adj[u]) if (v != p) {
      int res = (rank[v] < rank[u] ?
          self(self, v, u, lb, rank[u]) :
          self(self, v, u, rank[u], rb));
      if (res == -1) return -1;
      s += res, lt += (rank[v] < rank[u]);
    }
    return (lt > 1 or (int)size(adj[u]) - 2 > lt) ? -1 : s;
  };

  for (int i = 0; i < n; ++i)
    if (size(adj[i]) <= 2 and dfs(dfs, i, -1, INT_MIN, INT_MAX) == n)
      answer(true);
  answer(false);

  return 0;
}
