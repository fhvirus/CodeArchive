#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  const int di[4] = {1, -1, 0, 0};
  const int dj[4] = {0, 0, 1, -1};

  string a[10];
  const auto ok = [&](int i, int j) {
    return not (0 > i or i >= 10 or 0 > j or j >= 9 or a[i][j] == 'S');
  };

  while (cin >> a[0]) {
    int pi, pj, ei, ej;
    for (int i = 1; i < 10; ++i) cin >> a[i];
    for (int i = 0; i < 10; ++i)
      for (int j = 0; j < 9; ++j) {
        if (a[i][j] == 'P') pi = i, pj = j;
        if (a[i][j] == 'E') ei = i, ej = j;
      }

    bool can = false;
    vector<pair<int, int>> cur, nxt;
    a[pi][pj] = 'x';
    cur.emplace_back(pi, pj);
    for (int dis = 0; not empty(cur) and not can; ++dis) {
      nxt.clear();
      const auto add = [&](int i, int j) {
        if (not ok(i, j) or a[i][j] == 'x') return;
        a[i][j] = 'x';
        nxt.emplace_back(i, j);
      };
      for (auto [i, j] : cur) {
        if (i == ei and j == ej) {
          cout << dis << '\n';
          can = true;
          break;
        }
        for (int d : {0, 1, 2, 3}) {
          int ni = i + di[d], nj = j + dj[d];
          if (not ok(ni, nj)) continue;
          add(ni, nj);
          for (int t : {2, 3})
            add(ni + di[d] + di[d ^ t], nj + dj[d] + dj[d ^ t]);
        }
      }
      swap(cur, nxt);
    }

    if (not can) cout << 0 << '\n';
  }

  return 0;
}
