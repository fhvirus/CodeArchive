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

  for (int i = 1; i <= n; ++i)
    adj[0].emplace_back(i, 0);

  vector<int64_t> dis(n + 1, LONG_MAX);
  dis[0] = 0;

  for (int i = 0; i < n; ++i)
    for (int u = 0; u <= n; ++u) for (auto [v, w] : adj[u])
      if (dis[u] != LONG_MAX) dis[v] = min(dis[v], dis[u] + w);

  vector<bool> neg(n + 1, LONG_MAX);
  for (int u = 0; u <= n; ++u) for (auto [v, w] : adj[u])
    if (dis[u] != LONG_MAX and dis[v] > dis[u] + w) 
      neg[u] = true;

  vector<int> par(n + 1, -1);
  const auto find_neg_cycle = [&](const auto& dfs, int u) -> void {
    for (auto [v, w] : adj[u]) if (dis[v] > dis[u] + w and par[v] == -1) {
      dis[v] = dis[u] + w;
      par[v] = u;
      dfs(dfs, v);
    }
  };

  for (int u = 1; u <= n; ++u) {
    if (!neg[u]) continue;
    fill(begin(par), end(par), -1);
    find_neg_cycle(find_neg_cycle, u);
    if (par[u] == -1) continue;
    cout << "YES\n";
    vector<int> ans;
    for (int i = par[u]; i != u; i = par[i])
      ans.push_back(i);
    ans.push_back(u);
    reverse(begin(ans), end(ans));
    for (auto i : ans) cout << i << ' ';
    cout << u << '\n';
    exit(0);
  }

  cout << "NO\n";


  return 0;
}
