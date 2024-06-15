#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> dp(n + 1, INT_MAX);
  dp[n] = 0;

  for (int i = n; i > 0; --i) if (dp[i] < INT_MAX) {
    for (int t = i; t > 0; t /= 10) {
      int d = t % 10;
      dp[i - d] = min(dp[i - d], dp[i] + 1);
    }
  }

  cout << dp[0] << '\n';

  return 0;
}
