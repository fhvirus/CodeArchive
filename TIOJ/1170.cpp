#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<int> a(N + 1);
  for (int i = 1; i <= N; ++i) cin >> a[i];
  partial_sum(begin(a), end(a), begin(a));

  vector<vector<int>> dp(N, vector<int>(N, INT_MIN));
  for (int i = 0; i < N; ++i) dp[i][i] = 0;
  for (int len = 2; len <= N; ++len) {
    for (int l = 0, r = l + len; r <= N; ++l, ++r) {
      for (int k = l + 1; k < r; ++k)
        dp[l][r - 1] = max(dp[l][r - 1],
            (a[r] - a[k]) * (a[k] - a[l]) +
            max(dp[l][k - 1], dp[k][r - 1]));
    }
  }

  cout << dp[0][N - 1] << '\n';
  
  return 0;
}
