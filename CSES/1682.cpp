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

  vector<int> vis(n + 1), out(n + 1), stk;
  int num = 0, ans_1 = -1, ans_2 = -1;
  const auto dfs = [&](const auto& dfs, int u) -> int {
    int low = vis[u] = ++num;
    stk.push_back(u);
    for (int v : adj[u]) if (not out[v])
      low = min(low, vis[v] ?: dfs(dfs, v));
    if (low == vis[u]) {
      (ans_1 == -1 ? ans_1 : ans_2) = u;
      int v;
      do {
        v = stk.back(); stk.pop_back();
        out[v] = 1;
      } while (v != u);
    }
    return vis[u] = low;
  };

  for (int i = 1; i <= n; ++i)
    if (not vis[i]) dfs(dfs, i);

  if (ans_2 == -1)
    cout << "YES\n";
  else
    cout << "NO\n" << ans_1 << ' ' << ans_2 << '\n';

  return 0;
}
