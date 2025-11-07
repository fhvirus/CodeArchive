#include <bits/stdc++.h>
using namespace std;

const int kN = 1001;
int N, a[kN], dp[kN][kN];

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i)
    cin >> a[i];

  for (int l = 0; l + 1 < N; ++l)
    dp[2][l] = (a[l] == a[l + 1]);

  for (int len = 4; len <= N; len += 2)
    for (int l = 0; l + len - 1 < N; ++l) {
      int ans = dp[len - 2][l + 1] + (a[l] == a[l + len - 1]);
      for (int len_l = 2; len_l < len; len_l += 2)
        ans = max(ans, dp[len_l][l] + dp[len - len_l][l + len_l]);
      dp[len][l] = ans;
    }

  cout << dp[N][0] << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T --> 0) solve();

  return 0;
}
