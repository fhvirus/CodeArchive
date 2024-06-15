#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;

  int n, m;
  cin >> n >> m;

  vector<vector<int>> target(1 << n);
  for (int i = 0; i < (1 << n); ++i) {
    for (int j = i; ; j = (j - 1) & i) {
      bool can = true;
      for (int t = j; t > 0; t >>= 1) if (t & 1) {
        t >>= 1;
        can &= (t & 1);
      }
      if (can) target[i].push_back((i ^ ((1 << n) - 1)) | j);
      if (j == 0) break;
    }
  }

  vector<int> dp(1 << n), sc(1 << n);
  sc[(1 << n) - 1] = 1;

  for (int i = 0; i < m; ++i) {
    fill(begin(dp), end(dp), 0);
    for (int j = 0; j < (1 << n); ++j) {
      for (int k : target[j]) {
        dp[k] += sc[j];
        if (dp[k] >= MOD) dp[k] -= MOD;
      }
    }
    swap(dp, sc);
  }

  cout << sc[(1 << n) - 1] << '\n';

  return 0;
}
