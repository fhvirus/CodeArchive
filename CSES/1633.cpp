#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;

  int n;
  cin >> n;

  vector<int> dp(6);
  dp[0] = 1;
  int sum = 1;

  for (int i = 1; i <= n; ++i) {
    int t = dp[i % 6];
    dp[i % 6] = sum;
    sum = sum + (sum - t);
    if (sum >= MOD) sum -= MOD;
    if (sum < 0) sum += MOD;
  }

  cout << dp[n % 6] << '\n';

  return 0;
}
