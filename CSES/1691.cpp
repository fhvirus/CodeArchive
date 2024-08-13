#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i = a; i < (b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
  cin.tie(0) -> sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<vector<pii>> adj(n + 1);
  vi deg(n + 1);
  for (int u, v, i = 0; i < m; ++i) {
    cin >> u >> v;
    adj[u].emplace_back(v, i);
    adj[v].emplace_back(u, i);
    ++deg[u], ++deg[v];
  }

  for (int d : deg) if (d & 1)
    return cout << "IMPOSSIBLE\n", 0;

  vi ans, it(n + 1, 0);
  vector<bool> used(m);
  const auto dfs = [&](const auto& dfs, int u) -> void {
    for (int &i = it[u]; i < sz(adj[u]); ++i) {
      auto [v, e] = adj[u][i];
      if (used[e]) continue;
      used[e] = true;
      dfs(dfs, v);
    }
    ans.push_back(u);
  };

  dfs(dfs, 1);
  if (sz(ans) != m + 1)
    return cout << "IMPOSSIBLE\n", 0;

  rep (i, 0, m + 1)
    cout << ans[i] << " \n"[i == m];
}
