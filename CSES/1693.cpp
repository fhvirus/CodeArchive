#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<vi> adj(n + 1);
  vi deg(n + 1);
  for (int u, v, i = 0; i < m; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    deg[u] += 1, deg[v] -= 1;
  }

  for (int i = 1; i <= n; ++i)
    if (deg[i] - (i == 1) + (i == n) != 0)
      return cout << "IMPOSSIBLE\n", 0;

  vi ans, it(n + 1);
  const auto dfs = [&](const auto &dfs, int u) -> void {
    for (int &i = it[u]; i < sz(adj[u]); ) {
      int v = adj[u][i++];
      dfs(dfs, v);
    }
    ans.push_back(u);
  };
  dfs(dfs, 1);

  if (sz(ans) != m + 1)
    return cout << "IMPOSSIBLE\n", 0;
  reverse(all(ans));
  rep (i, 0, sz(ans))
    cout << ans[i] << " \n"[i + 1 == sz(ans)];

  return 0;
}
