#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;

  map<string, int> id;
  const auto get_id = [&](const string& s) {
    auto [it, _] = id.emplace(s, (int)size(id));
    return it->second;
  };

  vector<vector<int>> adj(n);
  for (int i = 0; i < n; ++i) {
    string a, b;
    cin >> a >> b;
    if (a == "=" and b == "=") break;
    int u = get_id(a), v = get_id(b);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int ans = 0;
  const auto dfs = [&](const auto& self, int u, int p) -> int {
    int mxd = 0;
    for (int v : adj[u]) if (v != p) {
      int vd = self(self, v, u) + 1;
      ans = max(ans, mxd + vd);
      mxd = max(mxd, vd);
    }
    return mxd;
  };
  dfs(dfs, 0, -1);
  cout << ans << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int k;
  cin >> k;
  while (k --> 0) solve();

  return 0;
}
