#include <bits/stdc++.h>
using namespace std;
 
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
 
  int n, m;
  cin >> n >> m;
 
  vector<vector<int>> adj(n + 1);
  for (int a, b, i = 0; i < m; ++i) {
    cin >> a >> b;
    adj[a].push_back(b);
  }
 
  vector<int> vis(n + 1), con(n + 1), stk;
  int num = 0, n_con = 0;
  const auto dfs = [&](const auto& dfs, int u) -> int {
    int low = vis[u] = ++num;
    stk.push_back(u);
    for (int v : adj[u]) if (con[v] == 0)
      low = min(low, vis[v] ?: dfs(dfs, v));
    if (low == vis[u]) {
      ++n_con;
      int v;
      do {
        v = stk.back(); stk.pop_back();
        con[v] = n_con;
      } while (v != u);
    }
    return vis[u] = low;
  };
 
  for (int i = 1; i <= n; ++i)
    if (not vis[i]) dfs(dfs, i);
 
  cout << n_con << '\n';
  for (int i = 1; i <= n; ++i)
    cout << con[i] << " \n"[i == n];
 
  return 0;
}
