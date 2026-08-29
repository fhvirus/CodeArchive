#include <bits/stdc++.h>
using namespace std;

template <class T> void chmin(T &a, T b) { if (a > b) a = b; }

void solve() {
  int n;
  cin >> n;

  vector<pair<int, int>> bok(n);
  int tot_t = 0;
  for (auto &[h, t] : bok) {
    cin >> h >> t;
    tot_t += t;
  }
  ranges::sort(bok, greater());

  vector dp(tot_t + 1, vector(tot_t + 1, INT_MAX));
  dp[0][0] = 0;
  int sum_t = 0;
  for (auto [h, t] : bok) {
    for (int i = sum_t; i >= 0; --i) {
      for (int j = sum_t - i; j >= 0; --j) if (dp[i][j] != INT_MAX) {
        chmin(dp[i + t][j], dp[i][j] + (i == 0 ? h : 0));
        chmin(dp[i][j + t], dp[i][j] + (j == 0 ? h : 0));
      }
    }
    sum_t += t;
  }

  int ans = INT_MAX;
  for (int i = 1; i < tot_t; ++i)
    for (int j = 1; i + j < tot_t; ++j) if (dp[i][j] != INT_MAX)
      chmin(ans, (dp[i][j] + bok[0].first) * max({i, j, tot_t - i - j}));

  cout << ans << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while (T --> 0) solve();

  return 0;
}
