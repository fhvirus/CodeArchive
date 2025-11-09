#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int m;
  cin >> m;

  vector g(m, vector<int>(m));
  for (int i = 0; i < m; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < m; ++j)
      g[i][j] = (s[j] == '1');
  }

  int s, t, N;
  cin >> s >> t >> N;

  vector<int> dp(m, 0), sc(m, 0);
  sc[s - 1] = 1;

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < m; ++j)
      dp[j] = inner_product(begin(g[j]), end(g[j]), begin(sc), 0);
    ans += dp[t - 1];
    swap(dp, sc);
  }

  cout << ans << '\n';

  return 0;
}
