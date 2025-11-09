#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<int> delay(n + 1), deg(n + 1);
  vector<vector<int>> conn(n + 1);
  
  for (int i = 1; i <= n; ++i) cin >> delay[i];
  for (int u, v, i = 0; i < m; ++i) {
    cin >> u >> v;
    conn[u].push_back(v);
    deg[v] += 1;
  }

  vector<int> ord;
  for (int i = 1; i <= n; ++i)
    if (deg[i] == 0) ord.push_back(i);

  for (int i = 0; i < n; ++i) {
    int u = ord[i];
    for (int v : conn[u])
      if ((--deg[v]) == 0)
        ord.push_back(v);
  }

  vector<int> dp(n + 1);
  for (int u : ord) {
    dp[u] += delay[u];
    for (int v : conn[u])
      dp[v] = max(dp[v], dp[u]);
  }

  vector<int> crit(n + 1);
  int max_delay = *max_element(begin(dp), end(dp));
  for (int i = 1; i <= n; ++i)
    if (dp[i] == max_delay) crit[i] = true;

  reverse(begin(ord), end(ord));
  int ans = 0;
  for (int u : ord) {
    for (int v : conn[u])
      if (dp[v] == dp[u] + delay[v])
        crit[u] |= crit[v];
    ans += crit[u];
  }

  cout << ans << '\n';

  return 0;
}
