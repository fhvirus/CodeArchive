#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int N, M; cin >> N >> M, N != 0; ) {
    vector<pair<int, int>> ps(M + 1);
    vector<int> T(M);
    for (int i = 0; i < M; ++i)
      cin >> ps[i].first >> ps[i].second >> T[i];
    ps[M] = {1, 1};

    vector dis(M + 1, vector<int>(M + 1, 0));
    for (int i = 0; i <= M; ++i)
      for (int j = i + 1; j <= M; ++j)
        dis[i][j] = dis[j][i] = abs(ps[i].first - ps[j].first) +
          abs(ps[i].second - ps[j].second);

    const auto get_t = [&T](int t, int i) { return (t + T[i] - 1) / T[i] * T[i]; };

    vector<int> dp((1 << M) * M, INT_MAX);
    for (int i = 1; i < (1 << M); ++i) {
      if ((i & (i - 1)) == 0) {
        int j = __lg(i);
        dp[i * M + j] = get_t(0 + dis[M][j], j);
        continue;
      }
      for (int j = 0; j < M; ++j) if (i >> j & 1)
        for (int k = 0; k < M; ++k) if (j != k and (i >> k & 1))
          dp[i * M + j] = min(dp[i * M + j],
              get_t(dp[(i ^ (1 << j)) * M + k] + dis[k][j], j));
    }

    cout <<  *min_element(end(dp) - M, end(dp)) << '\n';
  }

  return 0;
}
