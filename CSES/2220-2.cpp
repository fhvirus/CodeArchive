#include <bits/stdc++.h>
using namespace std;

int64_t solve(int64_t x) {
  if (x < 10) return x + 1;

  string s = to_string(x);
  int n = (int) s.size();
  s = '0' + s;

  vector<array<int64_t, 2>> dp(10), sc(10);
  sc[0][1] = 1;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 10; ++j)
      dp[j][0] = dp[j][1] = 0;

    if (s[i] != s[i + 1])
      dp[s[i + 1] - '0'][1] += sc[s[i] - '0'][1];

    for (int j = 0; j < s[i + 1] - '0'; ++j)
      if (j != s[i] - '0')
        dp[j][0] += sc[s[i] - '0'][1];

    for (int j = 0; j < 10; ++j)
      for (int k = 0; k < 10; ++k)
        if (j != k)
          dp[k][0] += sc[j][0];

    swap(dp, sc);
  }

  int64_t ans = 1, pow9 = 9;
  for (int i = 1; i < n; ++i, pow9 *= 9)
    ans += pow9;
  for (int i = 0; i < 10; ++i)
    ans += sc[i][0] + sc[i][1];

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int64_t a, b;
  cin >> a >> b;

  cout << solve(b) - solve(a - 1) << '\n';

  return 0;
}
