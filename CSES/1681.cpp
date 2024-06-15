#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  
  const int MOD = 1e9 + 7;

  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n + 1);
  vector<int> in(n + 1);
  for (int a, b, i = 0; i < m; ++i) {
    cin >> a >> b;
    adj[a].push_back(b);
    in[b] += 1;
  }

  queue<int> q;
  vector<int> dp(n + 1);
  dp[1] = 1;

  for (int i = 1; i <= n; ++i)
    if (in[i] == 0) q.push(i);

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      dp[v] += dp[u];
      if (dp[v] >= MOD) dp[v] -= MOD;
      in[v] -= 1;
      if (in[v] == 0) q.push(v);
    }
  }

  cout << dp[n] << '\n';

  return 0;
}
