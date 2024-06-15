#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int a, b;
  cin >> a >> b;

  vector dp(a + 1, vector<int>(b + 1, INT_MAX));

  dp[1][1] = 0;
  for (int i = 1; i <= a; ++i) {
    for (int j = 1; j <= b; ++j) {
      if (i == j) {
        dp[i][j] = 0;
        continue;
      }
      for (int k = 1; k < j; ++k)
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k] + 1);
      for (int k = 1; k < i; ++k)
        dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j] + 1);
    }
  }

  cout << dp[a][b] << '\n';

  return 0;
}
