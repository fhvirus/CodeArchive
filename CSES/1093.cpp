#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;

  int n;
  cin >> n;

  if (n * (n + 1) % 4 != 0) {
    cout << 0 << '\n';
    exit(0);
  }

  int t = n * (n + 1) / 4;

  vector<int> dp(t + 1);
  dp[0] = 1;
  for (int i = 1, sum = 0; i <= n; ++i) {
    for (int j = min(sum, t - i); j >= 0; --j) {
      dp[j + i] += dp[j];
      if (dp[j + i] >= MOD) dp[j + i] -= MOD;
    }
    sum += i;
  }

  cout << (dp[t] * (MOD + 1l) / 2) % MOD << '\n';

  return 0;
}
