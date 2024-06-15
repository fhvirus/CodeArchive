#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, int>>> adj(n + 1);
  for (int a, b, c, i = 0; i < m; ++i) {
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
  }

  vector<int64_t> dis(n + 1, LONG_MIN);
  dis[1] = 0;

  for (int i = 1; i < n; ++i)
    for (int u = 1; u <= n; ++u) for (auto [v, w] : adj[u])
      if (dis[u] != LONG_MIN) dis[v] = max(dis[v], dis[u] + w);

  vector<bool> on_pos_cyc(n + 1, false);
  for (int u = 1; u <= n; ++u) for (auto [v, w] : adj[u])
    if (dis[u] != LONG_MIN and dis[v] < dis[u] + w)
      on_pos_cyc[u] = true;

  queue<int> q;
  for (int i = 1; i <= n; ++i)
    if (on_pos_cyc[i]) q.push(i);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (auto [v, w] : adj[u]) if (!on_pos_cyc[v]) {
      on_pos_cyc[v] = 1;
      q.push(v);
    }
  }

  cout << (on_pos_cyc[n] ? -1 : dis[n]) << '\n';

  return 0;
}
