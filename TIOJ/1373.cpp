#include <bits/stdc++.h>
using namespace std;

const int kN = 100;
const int di[4] = {1, -1, 0, 0};
const int dj[4] = {0, 0, 1, -1};

int dis[kN][kN][4];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int m, n;
  cin >> m >> n;

  vector<string> a(m);
  for (auto &i : a) cin >> i;

  int si, sj, ei, ej;
  cin >> si >> sj >> ei >> ej;
  --si, --sj, --ei, --ej;

  for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
      fill_n(dis[i][j], 4, INT_MAX);

  vector<tuple<int, int, int>> cur, nxt;
  for (int d : {0, 1, 2, 3})
    dis[si][sj][d] = 0, cur.emplace_back(si, sj, d);

  for (int cd = 0; not empty(cur); ++cd) {
    while (not empty(cur)) {
      auto [i, j, d] = cur.back(); cur.pop_back();
      if (dis[i][j][d] != cd) continue;
      for (int nd : {0, 1, 2, 3}) {
        int ni = i + di[nd], nj = j + dj[nd];
        if (0 <= min(ni, nj) and ni < n and nj < m and
            a[ni][nj] == 'O' and dis[ni][nj][nd] > cd)
          dis[ni][nj][nd] = dis[i][j][d] + (nd != d),
            (nd != d ? nxt : cur).emplace_back(ni, nj, nd);
      }
    }
    cur.swap(nxt);
  }

  int ans = *min_element(dis[ei][ej], dis[ei][ej] + 4);
  if (ans == INT_MAX) cout << "No Way!!\n";
  else cout << ans << '\n';

  return 0;
}
