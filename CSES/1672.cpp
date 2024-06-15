#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m, q;
  cin >> n >> m >> q;

  vector dis(n + 1, vector<int64_t>(n + 1, LONG_MAX));
  for (int a, b, c, i = 0; i < m; ++i) {
    cin >> a >> b >> c;
    dis[b][a] = dis[a][b] = min(dis[a][b], (int64_t) c);
  }
  for (int i = 1; i <= n; ++i)
    dis[i][i] = 0;

  for (int k = 1; k <= n; ++k)
    for (int i = 1; i <= n; ++i) if (dis[i][k] < LONG_MAX)
      for (int j = 1; j <= n; ++j) if (dis[k][j] < LONG_MAX)
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

  for (int a, b, i = 0; i < q; ++i) {
    cin >> a >> b;
    cout << (dis[a][b] == LONG_MAX ? -1 : dis[a][b]) << '\n';
  }

  return 0;
}
