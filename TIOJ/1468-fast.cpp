#include <bits/stdc++.h>
using namespace std;

constexpr int pow3(int n) {
  int r = 1;
  while (n --> 0) r *= 3;
  return r;
}

int get_d(int v, int j) { return v >> (j * 2) & 0b11; }
int set_d(int v, int j, int d) { return (v & ~(0b11 << (j * 2))) | (d << (j * 2)); }

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<int> g(n);
  for (int x, y, i = 0; i < k; ++i) {
    cin >> x >> y;
    g[x - 1] |= (1 << (y - 1));
  }

  if (m == 1) {
    cout << 0 << '\n';
    return;
  }

  vector<pair<int, int>> sc, dp;
  sc.emplace_back(0 * 2 + 0, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      dp.clear();
      ranges::sort(sc);
      for (int l = 0, r; l < (int)size(sc); l = r) {
        auto [u, val] = sc[l];
        int state = u / 2, last = u % 2;
        for (r = l + 1; r < (int)size(sc) and u == sc[r].first; ++r)
          val = max(val, sc[r].second);

        if (g[i] >> (j - 1) & 0b11) {
          int to = set_d(state, j - 1, 0);
          dp.emplace_back(to * 2 + 0, val);
        } else {
          int d = last ? 0 : 1 + get_d(state, j - 1);
          int pd = j > 1 ? get_d(state, j - 2) : 0;
          // do nothing
          int to = set_d(state, j - 1, min(d, 2));
          dp.emplace_back(to * 2 + 0, val);
          // put horizontal
          if (d >= 3) {
            to = set_d(state, j - 1, 0);
            if (j > 1) to = set_d(to, j - 2, 0);
            if (j + 1 < m) to = set_d(to, j, 0);
            dp.emplace_back(to * 2 + (j != m - 1), val + 1);
          }
          // put vertical
          if (d >= 2 and pd >= 2) {
            to = set_d(state, j - 1, 0);
            to = set_d(to, j - 2, 0);
            if (j > 2) to = set_d(to, j - 3, 0);
            if (j + 1 < m) to = set_d(to, j, 0);
            dp.emplace_back(to * 2 + (j != m - 1), val + 1);
          }
        }
      }
      swap(dp, sc);
    }
  }

  int ans = INT_MIN;
  for (auto [_, val] : sc) ans = max(ans, val);
  cout << ans << '\n';
  return;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while (T --> 0) solve();

  return 0;
}
