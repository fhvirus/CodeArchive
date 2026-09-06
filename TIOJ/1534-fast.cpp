#include <bits/stdc++.h>
using namespace std;

template <class T> void chmin(T &a, T b) { if (a > b) a = b; }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int A, B, N, M;
  cin >> A >> B >> N >> M;

  vector dp(N + 1, vector(M + 1, INT_MAX));
  dp[0][0] = 0;
  for (int i = 0; i <= N; ++i) for (int j = 0; j <= i and i + j <= N; ++j) {
    for (int k = 0, sum_M = 0; sum_M <= M; ++sum_M) {
      while (k < sum_M and max(dp[i][k], dp[j][sum_M - k]) >=
          max(dp[i][k + 1], dp[j][sum_M - k - 1])) ++k;
      int val = max(dp[i][k], dp[j][sum_M - k]);
      if (i + j < N) chmin(dp[i + j + 1][sum_M], val + A);
      if (sum_M < M) chmin(dp[i + j][sum_M + 1], val + B);
    }
  }

  cout << dp[N][M] << '\n';

  return 0;
}
