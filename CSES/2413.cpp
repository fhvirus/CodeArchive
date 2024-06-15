#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;
  const int kN = 1e6;

  // dp[i][0]: together
  // dp[i][1]: split
  vector<array<int, 2>> dp(kN + 1);

  dp[1][0] = dp[1][1] = 1;
  for (int i = 2; i <= kN; ++i) {
    dp[i][0] = (int) ((2l * dp[i - 1][0] + dp[i - 1][1]) % MOD);
    dp[i][1] = (int) ((dp[i - 1][0] + 4l * dp[i - 1][1]) % MOD);
  }

  int t;
  cin >> t;

  while (t --> 0) {
    int n;
    cin >> n;
    cout << (dp[n][0] + dp[n][1]) % MOD << '\n';
  }


  return 0;
}
