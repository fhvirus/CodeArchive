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

  vi c(n + 1);
  rep (i, 1, n + 1) cin >> c[i];

  vector<vi> adj(n + 1);
  for (int u, v, i = 1; i < n; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vi ans(n + 1);
  function<set<int>(int, int)> dfs = [&](int u, int p) {
    set<int> s;
    s.insert(c[u]);
    for (int v : adj[u]) if (v != p) {
      auto t = dfs(v, u);
      if (sz(s) < sz(t)) swap(s, t);
      for (int i : t) s.insert(i);
    }
    ans[u] = sz(s);
    return s;
  };
  dfs(1, 1);

  rep (i, 1, n + 1) cout << ans[i] << " \n"[i == n];
}
