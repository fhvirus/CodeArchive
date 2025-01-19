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

  int n;
  cin >> n;

  vector<vi> adj(n + 1);
  for (int u, v, i = 1; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vi siz(n + 1, 1);
  vector<ll> ans(n + 1);

  function<void(int, int)> dfs1 = [&](int u, int p) {
    for (int v : adj[u]) if (v != p) {
      dfs1(v, u);
      siz[u] += siz[v];
      ans[u] += ans[v] + siz[v];
    }
  };
  function<void(int, int)> dfs2 = [&](int u, int p) {
    for (int v : adj[u]) if (v != p) {
      ans[v] += (ans[u] - ans[v] - siz[v] + n - siz[v]);
      dfs2(v, u);
    }
  };

  dfs1(1, 1);
  dfs2(1, 1);

  rep (i, 1, n + 1)
    cout << ans[i] << " \n"[i == n];
}
