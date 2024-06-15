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

  vector<int> par(n + 1);
  vector<bool> in(n + 1);
  int s = 0;
  const auto dfs = [&](const auto& dfs, int u) -> void {
    in[u] = true;
    for (int v : adj[u]) {
      if (par[v] == 0) {
        par[v] = u;
        dfs(dfs, v);
      } else if (in[v]) {
        par[v] = u;
        s = v;
      }
      if (s != 0) break;
    }
    in[u] = false;
  };

  for (int i = 1; i <= n; ++i) {
    if (par[i] == 0) {
      par[i] = i;
      dfs(dfs, i);
    }
  }

  if (s == 0) {
    cout << "IMPOSSIBLE\n";
    exit(0);
  }

  vector<int> ans;
  for (int u = par[s]; u != s; u = par[u])
    ans.push_back(u);
  ans.push_back(s);
  reverse(begin(ans), end(ans));

  cout << ans.size() + 1 << '\n';
  for (int i : ans) cout << i << ' ';
  cout << s << '\n';

  return 0;
}
