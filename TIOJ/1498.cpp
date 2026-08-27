#include <bits/stdc++.h>
using namespace std;

const int kN = 100;
const int dir[5] = {0, 1, 0, -1, 0};
int16_t dis[kN][kN][kN];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m, k, sx, sy, tx, ty;
  cin >> n >> m >> k >> sx >> sy >> tx >> ty;
  --sx, --sy, --tx, --ty;

  if (int d = abs(tx - sx) + abs(ty - sy); d / 2 <= k) {
    cout << d << '\n';
    exit(0);
  }

  vector<string> g(n);
  for (auto &i : g) cin >> i;

  queue<tuple<int, int, int>> q;
  dis[0][sx][sy] = 1, q.emplace(0, sx, sy);
  int ans = INT_MAX;
  while (not empty(q)) {
    auto [p, i, j] = q.front(); q.pop();
    if (i == tx and j == ty) { ans = dis[p][i][j] - 1; break; }
    for (int d : {0, 1, 2, 3}) {
      int ni = i + dir[d], nj = j + dir[d + 1];
      if (0 > min(ni, nj) or ni >= n or nj >= m) continue;
      int np = p + (g[i][j] == '0' and g[ni][nj] == '1');
      if (np > k or dis[np][ni][nj] != 0) continue;
      dis[np][ni][nj] = dis[p][i][j] + 1, q.emplace(np, ni, nj);
    }
  }

  if (ans == INT_MAX) cout << "I WEAR A RUBBER AT ALL TIMES ITS A NECESSITY\n";
  else cout << ans << '\n';

  return 0;
}
