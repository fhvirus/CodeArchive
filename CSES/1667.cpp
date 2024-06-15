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

  vector<int> sc(n + 1, -1);
  queue<int> q;
  sc[1] = 0;
  q.push(1);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) if (sc[v] == -1) {
      sc[v] = u;
      q.push(v);
    }
  }

  if (sc[n] == -1) {
    cout << "IMPOSSIBLE\n";
    exit(0);
  }

  vector<int> ans;
  for (int u = n; u != 0; u = sc[u])
    ans.push_back(u);
  reverse(begin(ans), end(ans));

  cout << ans.size() << '\n';
  for (int i : ans)
    cout << i << " \n"[i == n];


  return 0;
}
