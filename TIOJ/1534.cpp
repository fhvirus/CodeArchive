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

  for (int i = 0; i <= N; ++i) for (int j = 0; j <= M; ++j) {
    for (int k = 0; k <= i and i + k <= N; ++k) for (int l = 0; j + l <= M; ++l) {
      if (i + k + 1 <= N) chmin(dp[i + k + 1][j + l], max(dp[i][j], dp[k][l]) + A);
      if (j + l + 1 <= M) chmin(dp[i + k][j + l + 1], max(dp[i][j], dp[k][l]) + B);
    }
  }

  cout << dp[N][M] << '\n';

  return 0;
}
