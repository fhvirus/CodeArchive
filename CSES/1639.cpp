#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s, t;
  cin >> s >> t;

  int n = (int) s.size(), m = (int) t.size();

  vector<int> dp(m + 1), sc(m + 1);
  iota(begin(sc), end(sc), 0);

  for (int i = 1; i <= n; ++i) {
    dp[0] = i;
    for (int j = 1; j <= m; ++j) {
      if (s[i - 1] == t[j - 1])
        dp[j] = sc[j - 1];
      else
        dp[j] = min({ sc[j - 1], sc[j], dp[j - 1] }) + 1;
    }
    swap(dp, sc);
  }

  cout << sc[m] << '\n';

  return 0;
}
