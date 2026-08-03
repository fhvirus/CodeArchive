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

    const auto go = [&](const auto& self, int u, int p) -> vector<array<int, 2>> {
      vector<array<int, 2>> dp(1, {0, 1});
      for (int v : adj[u]) if (v != p) {
        auto sc = self(self, v, u);
        dp.resize(size(dp) + size(sc), dp.back());
        for (int i = (int)size(dp) - 1; i >= 0; --i) {
          array<int, 2> t = {INT_MIN / 2, INT_MIN / 2};
          for (int j = 0; j < (int)size(sc) and j <= i; ++j) {
            t[0] = max(t[0], dp[i - j][0] + sc[j][0]);
            if (i - j - 1 >= 0)
              t[0] = max(t[0], dp[i - j - 1][0] + sc[j][1]);
            t[1] = max(t[1], dp[i - j][1] + sc[j][1]);
            if (i - j - 1 >= 0)
              t[1] = max(t[1], dp[i - j - 1][1] + sc[j][0]);
          }
          dp[i] = t;
        }
      }
      if (bad[u]) for (auto &i : dp) i[1] = INT_MIN / 2;
      return dp;
    };

    auto dp = go(go, 0, -1);
    int ans = -1;
    for (int i = 0; i < (int)size(dp); ++i)
      if (max(dp[i][0], dp[i][1]) >= k) { ans = i; break; }

    if (ans == -1) cout << "ACM rules!\n";
    else cout << ans << '\n';
  }

  return 0;
}
