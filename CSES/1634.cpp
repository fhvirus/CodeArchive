#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, x;
  cin >> n >> x;

  vector<int> c(n);
  for (int &i : c) cin >> i;

  vector<int> dp(x + 1, INT_MAX);
  dp[0] = 0;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j + c[i] <= x; ++j)
      if (dp[j] < INT_MAX)
        dp[j + c[i]] = min(dp[j + c[i]], dp[j] + 1);

  cout << (dp[x] == INT_MAX ? -1 : dp[x]) << '\n';

  return 0;
}
