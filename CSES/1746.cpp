#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;

  int n, m;
  cin >> n >> m;

  vector<int> x(n);
  for (int &i : x) cin >> i;

  vector<int> dp(m + 2), sc(m + 2);
  if (x[0] == 0) fill(begin(sc) + 1, begin(sc) + m + 1, 1);
  else sc[x[0]] = 1;

  for (int i = 1; i < n; ++i) {
    if (x[i] == 0) {
      for (int j = 1; j <= m; ++j) {
        dp[j] = (int) ((0l + sc[j - 1] + sc[j] + sc[j + 1]) % MOD);
      }
    } else {
      fill(begin(dp), end(dp), 0);
      dp[x[i]] = (int) ((0l + sc[x[i] - 1] + sc[x[i]] + sc[x[i] + 1]) % MOD);
    }
    swap(dp, sc);
  }

  cout << accumulate(begin(sc), end(sc), 0l) % MOD << '\n';

  return 0;
}
