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

  int n, q;
  cin >> n >> q;

  vector<vi> adj(n + 1);
  for (int u, v, i = 1; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int l = __lg(n) + 1;
  vector<vi> e(l, vi(n + 1));
  vi dep(n + 1);
  const function<void(int, int)> dfs = [&](int u, int p) {
    dep[u] = dep[p] + 1;
    e[0][u] = p;
    for (int v : adj[u]) if (v != p) dfs(v, u);
  };
  dfs(1, 1);

  rep (i, 1, l) rep(j, 1, n + 1)
    e[i][j] = e[i - 1][e[i - 1][j]];

  const auto lca = [&](int u, int v) -> int {
    if (dep[u] < dep[v]) swap(u, v);
    for (int d = dep[u] - dep[v], i = 0; i < l; ++i)
      if (d >> i & 1) u = e[i][u];
    if (u == v) return u;
    for (int i = l - 1; i >= 0; --i) {
      int a = e[i][u], b = e[i][v];
      if (a != b) u = a, v = b;
    }
    return e[0][u];
  };

  for (int a, b; q--; ) {
    cin >> a >> b;
    cout << dep[a] + dep[b] - 2 * dep[lca(a, b)] << '\n';
  }
}
