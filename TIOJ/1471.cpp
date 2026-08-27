#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int mod = 1'000'000'000;

  int n;
  cin >> n;
  n /= 2;

  vector dp(n + 1, vector<int>(n + 1));
  vector<int> sum(n + 1);

  dp[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) {
      dp[i][j] = (dp[i - 1][j - 1] + sum[j]) % mod;
      sum[j] = (sum[j] - dp[i - j][j] + dp[i][j]);
      sum[j] -= ((sum[j] >= mod) - (sum[j] < 0)) * mod;
    }
  }

  auto ans = accumulate(begin(dp[n]), end(dp[n]), 0l) % mod;
  if (n >= 22) cout << setw(9) << setfill('0') << fixed;
  cout << ans << endl;

  return 0;
}
