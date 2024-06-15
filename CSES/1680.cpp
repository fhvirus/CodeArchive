#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

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
  vector<int> dis(n + 1, INT_MIN), par(n + 1);
  dis[1] = 0;
  for (int i = 1; i <= n; ++i)
    if (in[i] == 0) q.push(i);

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (dis[v] < dis[u] + 1) {
        dis[v] = dis[u] + 1;
        par[v] = u;
      }
      in[v] -= 1;
      if (in[v] == 0) q.push(v);
    }
  }

  if (dis[n] < 0) {
    cout << "IMPOSSIBLE\n";
    exit(0);
  }

  vector<int> ans;
  for (int u = n; u != 0; u = par[u])
    ans.push_back(u);
  
  cout << ans.size() << '\n';
  for (int i = (int) ans.size() - 1; i >= 0; --i)
    cout << ans[i] << " \n"[i == 0];

  return 0;
}
