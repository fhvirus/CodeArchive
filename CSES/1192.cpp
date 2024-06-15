#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int dir[5] = {0, 1, 0, -1, 0};

  int n, m;
  cin >> n >> m;

  vector<string> g(n);
  for (string &i : g) cin >> i;

  int ans = 0;
  queue<pair<int, int>> q;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (g[i][j] == '#') continue;
      ans += 1;
      q.emplace(i, j);
      g[i][j] = '#';
      while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int d = 0; d < 4; ++d) {
          int nx = x + dir[d], ny = y + dir[d + 1];
          if (0 > nx or nx >= n or 0 > ny or ny >= m or g[nx][ny] == '#') continue;
          q.emplace(nx, ny);
          g[nx][ny] = '#';
        }
      }
    }
  }

  cout << ans << '\n';

  return 0;
}
