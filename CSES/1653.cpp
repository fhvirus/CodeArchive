#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, x;
  cin >> n >> x;

  vector<int> w(n);
  for (int &i : w) cin >> i;

  vector<pair<int, int>> dp(1 << n, pair<int, int>(n + 1, x + 1));
  dp[0] = pair<int, int>(0, 0);
  for (int i = 1; i < (1 << n); ++i) {
    for (int j = 0; j < n; ++j) if (i >> j & 1) {
      pair<int, int> val = dp[i ^ (1 << j)];
      if (val.second + w[j] <= x)
        val.second += w[j];
      else
        val.first += 1, val.second = w[j];
      dp[i] = min(dp[i], val);
    }
  }

  cout << dp[(1 << n) - 1].first + 1 << '\n';

  return 0;
}
