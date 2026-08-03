#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const int kG = 12;
int dis[kG + 2][4][kG + 2][4];
int dp[1 << kG][kG][4];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int m, n; cin >> m >> n >> ws; ) {
    string s;
    pair<int, int> ps, pe;
    vector<pair<int, int>> pg;
    for (int i = 0; i < m; ++i) {
      getline(cin, s);
      getline(cin, s);
      for (int j = 0; j < n; ++j) {
        char c = s[2 + 4 * j];
        if (c == 'S') ps = {i, j};
        if (c == 'E') pe = {i, j};
        if (c == 'G') pg.emplace_back(i, j);
      }
    }
    getline(cin, s);

    int k = (int)size(pg);
    pg.insert(end(pg), {ps, pe});
    for (int i = 0; i < k + 2; ++i)
      for (int j = 0; j < k + 2; ++j) if (i != j) {
        int dif_x = pg[j].first - pg[i].first,
            dif_y = pg[j].second - pg[i].second;
        for (int id : {0, 1, 2, 3})
          for (int jd : {0, 1, 2, 3}) {
            bool turn = (dif_x != 0 and dif_y != 0);
            bool bad_i = (i < k and dif_x * dx[id] + dif_y * dy[id] <= 0);
            bool bad_j = (j < k and dif_x * dx[jd] + dif_y * dy[jd] <= 0);
            dis[i][id][j][jd] = abs(dif_x) + abs(dif_y) + turn + bad_i +
              (bad_j or (not bad_i and not bad_j and turn and id == jd));
          }
      }

    for (int i = 1; i < (1 << k); ++i) {
      if ((i & (i - 1)) == 0) {
        for (int j = __lg(i), d = 0; d < 4; ++d)
          dp[i][j][d] = dis[k][0][j][d];
        continue;
      }
      for (int u = i; u; u ^= u & -u) {
        int j = __lg(u & -u);
        for (int dj : {0, 1, 2, 3}) {
          int res = INT_MAX;
          for (int v = i ^ (1 << j); v; v ^= v & -v) {
            int t = __lg(v & -v);
            for (int dt : {0, 1, 2, 3})
              res = min(res, dp[i ^ (1 << j)][t][dt] + dis[t][dt][j][dj]);
          }
          dp[i][j][dj] = res;
        }
      }
    }

    int ans = INT_MAX;
    for (int j = 0; j < k; ++j)
      for (int dj : {0, 1, 2, 3})
        ans = min(ans, dp[(1 << k) - 1][j][dj] + dis[j][dj][k + 1][0]);

    cout << ans << '\n';
  }


  return 0;
}
