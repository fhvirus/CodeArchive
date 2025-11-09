#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int m;
  cin >> m;

  vector D(m, vector<int>(m));
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < m; ++j)
      cin >> D[i][j], assert(D[i][j] <= 1000000);

  vector<int> a(1, 2);
  for (int v; cin >> v; a.push_back(v - 1));

  vector sc(m, vector<int>(m, INT_MAX / 2)), dp = sc;
  sc[0][1] = 0;
  for (int t = 1; t < (int) a.size(); ++t) {
    int u = a[t - 1], v = a[t];
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < m; ++j)
        dp[i][j] = sc[i][j] + D[u][v];
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
        dp[j][u] = min(dp[j][u], sc[i][j] + D[i][v]);
        dp[i][u] = min(dp[i][u], sc[i][j] + D[j][v]);
      }
    }

    swap(dp, sc);
  }

  int ans = INT_MAX;
  for (int i = 0; i < m; ++i)
    ans = min(ans, *min_element(begin(sc[i]), end(sc[i])));
  cout << ans << '\n';

  return 0;
}
