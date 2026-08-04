#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n, m, d; cin >> n >> m >> d; ) {
    vector g(n, vector(n, d + 1));
    for (int u, v, c, i = 0; i < m; ++i) {
      cin >> u >> v >> c;
      g[u][v] = g[v][u] = c;
    }

    vector<int> dp((1 << (n - 1)) * n, d + 1);
    const auto id = [&](int i, int j) {
      return ((i >> (n - 1) & 1) ? (~i & ((1 << n) - 1)) : i) * n + j; };

    for (int i = 1; i < (1 << n); ++i) {
      if ((i & (i - 1)) == 0) {
        dp[id(i, __lg(i))] = 0;
        continue;
      }

      for (int mj = i; mj; mj -= mj & -mj) {
        int j = __lg(mj & -mj);
        int &v = dp[id(i, j)];
        for (int mk = i ^ (1 << j); mk; mk -= mk & -mk) {
          int k = __lg(mk & -mk);
          v = min(v, dp[id(i ^ (1 << j), k)] + g[j][k]);
        }
      }
    }
    cout << (*min_element(begin(dp), begin(dp) + n) <= d ? "OK\n" : "...\n");
  }

  return 0;
}
