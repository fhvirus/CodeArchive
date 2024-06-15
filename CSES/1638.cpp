#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;

  int n;
  cin >> n;

  vector<string> grid(n);
  for (string &s: grid)
    cin >> s;

  vector dp(n, vector<int>(n));
  dp[0][0] = (grid[0][0] == '.');

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) if (grid[i][j] == '.') {
      if (i > 0) dp[i][j] += dp[i - 1][j];
      if (j > 0) dp[i][j] += dp[i][j - 1];
      if (dp[i][j] >= MOD) dp[i][j] -= MOD;
    }
  }

  cout << dp[n - 1][n - 1] << '\n';

  return 0;
}
