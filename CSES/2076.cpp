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

  vector<pii> es(m);
  vector<vector<pii>> adj(n + 1);
  rep (i, 0, m) {
    auto &[a, b] = es[i];
    cin >> a >> b;
    adj[a].emplace_back(b, i);
    adj[b].emplace_back(a, i);
  }

  vector<pii> bridges;
  vi num(n + 1);
  int tot = 0;
  const auto dfs = [&](const auto &dfs, int u, int pe) -> int {
    int low = num[u] = ++tot;
    for (auto [v, e] : adj[u]) if (e != pe) {
      if (num[v]) low = min(low, num[v]);
      else {
        int vlow = dfs(dfs, v, e);
        low = min(low, vlow);
        if (vlow > num[u])
          bridges.push_back(es[e]);
      }
    }
    return low;
  };

  dfs(dfs, 1, -1);

  rep (i, 1, n + 1) if (num[i] == 0) {
    bridges = es;
    break;
  }

  cout << sz(bridges) << '\n';
  for (auto [u, v] : bridges)
    cout << u << ' ' << v << '\n';

  return 0;
}
