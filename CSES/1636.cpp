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

  for (int i = 0; i < n; ++i) {
    for (int j = c[i]; j <= x; ++j) {
      dp[j] += dp[j - c[i]];
      if (dp[j] >= MOD) dp[j] -= MOD;
    }
  }

  cout << dp[x] << '\n';

  return 0;
}
