#include <bits/stdc++.h>
using namespace std;

const double INF = 1e9;
const int kN = 17;
double dp[1 << kN][kN + 1][kN + 1];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int n, v; cin >> n >> v, n or v; ) {
    vector<int64_t> x(n + 1), y(n + 1);
    for (int i = 0; i < n; ++i)
      cin >> x[i] >> y[i];

    for (int i = 0; i < (1 << n); ++i)
      for (int j = 0; j <= n; ++j)
        fill(dp[i][j], dp[i][j] + n + 1, INF);
    for (int i = 0; i <= n; ++i) dp[0][n][i] = 0;

    vector dis(n + 1, vector<double>(n + 1));
    for (int a = 0; a <= n; ++a)
      for (int b = 0; b <= n; ++b)
          dis[a][b] = sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b])) / v;

    for (int i = 0; i < (1 << n); ++i) {
      int left = n - popcount(unsigned(i));
      for (int a = 0; a <= n; ++a) if ((i >> a & 1) or a == n) {
        for (int b = 0; b < n; ++b) if ((i >> b & 1) == 0) {
          double tid = (720 + double(x[b]) / 2000.0) * 60, need = dis[a][b] * 2;
          for (int j = 1; j <= left; ++j, need *= 2) {
            double arrive = dp[i][a][j] + need;
            if (arrive >= tid) continue;
            auto &des = dp[i | (1 << b)][b][j - 1];
            des = min(des, arrive);
          }
        }
        for (int j = 1; j <= left; ++j)
          dp[i][n][j] = min(dp[i][n][j], dp[i][a][0] + dis[a][n]);
      }
    }

    int ans = 0;
    for (int i = 1; i < (1 << n); ++i) {
      int cnt = popcount(unsigned(i));
      for (int j = 0; j <= n; ++j)
        if (dp[i][j][0] < INF) ans = max(ans, cnt);
    }
    cout << ans << '\n';
  }

  return 0;
}
