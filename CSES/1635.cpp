#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;

  int n, x;
  cin >> n >> x;

  vector<int> c(n);
  for (int &i : c) cin >> i;

  vector<int> dp(x + 1, 0);
  dp[0] = 1;

  for (int i = 0; i <= x; ++i) {
    for (int j = 0; j < n; ++j) if (c[j] <= i) {
      dp[i] += dp[i - c[j]];
      if (dp[i] >= MOD) dp[i] -= MOD;
    }
  }

  cout << dp[x] << '\n';

  return 0;
}
