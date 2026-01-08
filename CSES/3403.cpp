#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<int> a(n), b(m);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;
  
  vector dp(n + 1, vector<int>(m + 1)), sc = dp;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (a[i] == b[j])
        dp[i + 1][j + 1] = dp[i][j] + 1, sc[i + 1][j + 1] = 3;
      else {
        if (dp[i][j + 1] < dp[i + 1][j])
          dp[i + 1][j + 1] = dp[i + 1][j], sc[i + 1][j + 1] = 1;
        else
          dp[i + 1][j + 1] = dp[i][j + 1], sc[i + 1][j + 1] = 2;
      }
    }
  }

  vector<int> ans;
  for (int i = n, j = m; sc[i][j]; ) {
    int t = sc[i][j];
    if (t == 3) ans.push_back(a[i - 1]);
    i -= (t >> 1 & 1), j -= (t & 1);
  }

  cout << ans.size() << '\n';
  for (int i : ans | views::reverse) cout << i << ' ';
  cout << '\n';

  return 0;
}
