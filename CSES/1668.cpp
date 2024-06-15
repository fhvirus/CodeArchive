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

  vector<int> color(n + 1);
  queue<int> q;
  for (int i = 1; i <= n; ++i) if (color[i] == 0) {
    color[i] = 1;
    q.push(i);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : adj[u]) {
        if (color[u] == color[v]) {
          cout << "IMPOSSIBLE\n";
          exit(0);
        }
        if (color[v] == 0) {
          color[v] = 3 - color[u];
          q.push(v);
        }
      }
    }
  }

  for (int i = 1; i <= n; ++i)
    cout << color[i] << " \n"[i == n];

  return 0;
}
