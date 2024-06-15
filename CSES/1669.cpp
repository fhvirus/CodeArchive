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
    adj[b].push_back(a);
  }

  vector<bool> vis(n + 1);
  bool put = false;
  vector<int> ans;
  const auto dfs = [&](const auto &dfs, int u, int p) -> void {
    vis[u] = true;
    for (int v : adj[u]) if (v != p) {
      if (vis[v]) {
        ans.push_back(v);
        put = true;
      } else dfs(dfs, v, u);
      if (put) {
        ans.push_back(u);
        if (u == ans[0]) {
          cout << ans.size() << '\n';
          for (int i = 0; i < (int) ans.size(); ++i)
            cout << ans[i] << " \n"[i == (int) ans.size() - 1];
          exit(0);
        }
        return;
      }
    }
  };

  for (int i = 1; i <= n; ++i)
    if (!vis[i]) dfs(dfs, i, 0);

  cout << "IMPOSSIBLE\n";

  return 0;
}
