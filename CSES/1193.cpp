#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int dir[5] = {0, 1, 0, -1, 0};
  const char op[5] = "RDLU";

  int n, m;
  cin >> n >> m;

  vector<string> g(n);
  for (string &i : g) cin >> i;

  int ai = 0, aj = 0, bi = 0, bj = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == 'A')
        ai = i, aj = j;
      if (g[i][j] == 'B')
        bi = i, bj = j;
    }
  }

  queue<pair<int, int>> q;
  q.emplace(ai, aj);
  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();
    for (int d = 0; d < 4; ++d) {
      int ni = i + dir[d], nj = j + dir[d + 1];
      if (0 > ni or ni >= n or 0 > nj or nj >= m or (g[ni][nj] != '.' and g[ni][nj] != 'B'))
        continue;
      g[ni][nj] = (char) d;
      q.emplace(ni, nj);
    }
  }

  if (g[bi][bj] == 'B') {
    cout << "NO\n";
    exit(0);
  }

  cout << "YES\n";

  string ans;
  for (int i = bi, j = bj; i != ai or j != aj; ) {
    ans.push_back(op[(int) g[i][j]]);
    tie(i, j) = make_pair(i - dir[(int) g[i][j]], j - dir[(int) g[i][j] + 1]);
  }
  reverse(begin(ans), end(ans));

  cout << ans.size() << '\n';
  cout << ans << '\n';

  return 0;
}
