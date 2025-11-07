#include <bits/stdc++.h>
using namespace std;

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

struct Rect { int l, u, r, d; };
int dist(const Rect& a, const Rect& b) {
  return max(0, max(a.l, b.l) - min(a.r, b.r)) +
      max(0, max(a.u, b.u) - min(a.d, b.d));
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  while (cin >> n >> m) {
    vector<Rect> rect(m + 2);
    for (int i = 1; i <= m; ++i) {
      auto &[l, u, r, d] = rect[i];
      cin >> l >> u >> r >> d;
    }

    vector dis(m + 2, vector<int>(m + 2));
    for (int i = 1; i <= m; ++i)
      for (int j = 1; j < i; ++j)
        dis[i][j] = dis[j][i] = dist(rect[i], rect[j]);

    int t;
    cin >> t;
    while (t --> 0) {
      int k, sx, sy, tx, ty;
      cin >> k >> sx >> sy >> tx >> ty;
      k += 1;

      rect[0] = {sx, sy, sx, sy};
      rect[m + 1] = {tx, ty, tx, ty};
      for (int i = 0; i <= m + 1; ++i) {
        dis[0][i] = dist(rect[0], rect[i]);
        dis[i][m + 1] = dist(rect[m + 1], rect[i]);
      }

      vector<int> dp(m + 2, INT_MAX / 2), sc;
      dp[0] = 0;
      while (k --> 0) {
        sc = dp;
        for (int i = 0; i <= m + 1; ++i)
          for (int j = 0; j <= m + 1; ++j)
            dp[j] = min(dp[j], sc[i] + dis[i][j]);
      }

      cout << dp[m + 1] << '\n';
    }
  }

  return 0;
}
