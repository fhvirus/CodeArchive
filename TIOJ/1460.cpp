#include <bits/stdc++.h>
using namespace std;

const int dir[5] = {0, 1, 0, -1, 0};
const int kN = 500;
int n, m, a[kN][kN];

bool ok(int i, int j) { return 0 <= min(i, j) and max(i, j) < n; }

void solve() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> a[i][j];

  vector<pair<int, int>> cur, nxt;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      bool low = true;
      for (int d : {0, 1, 2, 3}) {
        int ni = i + dir[d], nj = j + dir[d + 1];
        low &= (not ok(ni, nj) or a[i][j] < a[ni][nj]);
      }
      if (low) a[i][j] *= -1, cur.emplace_back(i, j);
    }

  if (m < (int)size(cur)) {
    cout << "Impossible\n";
    return;
  }

  int t = -1;
  for (; not empty(cur); swap(cur, nxt), ++t) {
    nxt.clear();
    for (auto [i, j] : cur)
      for (int d : {0, 1, 2, 3}) {
        int ni = i + dir[d], nj = j + dir[d + 1];
        if (ok(ni, nj) and -a[i][j] < a[ni][nj])
          a[ni][nj] *= -1, nxt.emplace_back(ni, nj);
      }
  }
  cout << t << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int t;
  cin >> t;
  while (t --> 0) solve();

  return 0;
}
