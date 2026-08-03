#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n, k, c; cin >> n >> k >> c; ) {
    vector<bool> bad(n);
    for (int u, i = 0; i < c; ++i) {
      cin >> u;
      bad[u] = true;
    }

    vector<vector<int>> adj(n);
    for (int u, v, i = 1; i < n; ++i) {
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    const auto eat = [](const auto& a, const auto& b, auto& c, int d) {
      for (int i = 0; i < (int)size(a); ++i)
        for (int j = 0; j < (int)size(b); ++j)
          c[i + j + d] = max(c[i + j + d], a[i] + b[j]);
    };
    const auto go = [&](const auto& self, int u, int p) -> pair<vector<int>, vector<int>> {
      vector<int> dp0(1, 0), dp1(1, bad[u] ? INT_MIN / 2 : 1);
      for (int v : adj[u]) if (v != p) {
        auto [sc0, sc1] = self(self, v, u);
        vector<int> tmp(size(dp0) + max(size(sc0), size(sc1) + 1) - 1, INT_MIN / 2);
        eat(dp0, sc0, tmp, 0);
        eat(dp0, sc1, tmp, 1);
        swap(tmp, dp0);
        if (not bad[u]) {
          tmp.assign(size(dp1) + max(size(sc0) + 1, size(sc1)) - 1, INT_MIN / 2);
          eat(dp1, sc0, tmp, 1);
          eat(dp1, sc1, tmp, 0);
          swap(dp1, tmp);
        }
      }
      return {dp0, dp1};
    };

    auto [dp0, dp1] = go(go, 0, -1);
    int ans = INT_MAX;
    for (int i = 0; i < (int)size(dp0); ++i) if (dp0[i] >= k) { ans = i; break; }
    for (int i = 0; i < (int)size(dp1); ++i) if (dp1[i] >= k) { ans = min(ans, i); break; }

    if (ans == INT_MAX) cout << "ACM rules!\n";
    else cout << ans << '\n';
  }

  return 0;
}
