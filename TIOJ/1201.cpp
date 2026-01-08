#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int n, m, k, p; cin >> n >> m >> k >> p, n; ) {
    vector<int64_t> dp(k + 1); dp[0] = 1;
    int64_t mul = 1;
    for (int i = 1; i <= k; ++i) {
      dp[i] = (dp[i - 1] * n + dp[max(0, i - m - 1)] * mul) % p;
      if (i <= m) mul = mul * n % p;
    }
    cout << dp[k] << '\n';
  }

  return 0;
}
