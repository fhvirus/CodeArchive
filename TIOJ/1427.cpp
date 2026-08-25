#include <bits/stdc++.h>
using namespace std;

template <class T>
void chmax(T& a, T b) { if (a < b) a = b; }

const int kN = 5000;
const int kK = 10;

int buf[2][kN + 1][kK + 1][2];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int m, n, k;
  cin >> m >> n >> k;

  string s, t;
  cin >> s >> t;

  auto sc = buf[0], dp = buf[1];
  for (int j = 0; j <= n; ++j)
    for (int l = 0; l <= k; ++l)
      sc[j][l][0] = sc[j][l][1] = INT_MIN;
  sc[0][0][0] = 0;

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j <= n; ++j)
      for (int l = 0; l <= k; ++l)
        dp[j][l][0] = dp[j][l][1] = INT_MIN;
    for (int j = 0; j < n; ++j) {
      if (s[i] == t[j]) {
        for (int l = 0; l < k; ++l) // new segment
          chmax(dp[j + 1][l + 1][1], sc[j][l][0] + (s[i] == 'a') * 2);
        for (int l = 0; l <= k; ++l) // extend segment
          chmax(dp[j + 1][l][1], sc[j][l][1] + (s[i] == 'a') * 2);
      }
      for (int l = 0; l <= k; ++l) {
        int v = max(sc[j][l][0], sc[j][l][1]);
        chmax(sc[j + 1][l][0], v);
        chmax(dp[j][l][0], v);
      }
    }
    swap(dp, sc);
  }

  int ans = 0;
  for (int j = 0; j <= n; ++j)
    for (int l = 0; l <= k; ++l)
      chmax(ans, max(sc[j][l][0], sc[j][l][1]));
  cout << ans << '\n';

  return 0;
}
