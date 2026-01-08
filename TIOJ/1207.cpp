#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  const int dx[4] = {1, -1, 0, 0};
  const int dy[4] = {0, 0, 1, -1};

  for (int B, S; cin >> B >> S; ) {
    int l = -1, d = -1, r = 1, u = 1;
    vector<pair<int, int>> ps(B);
    for (auto &[x, y] : ps) {
      cin >> x >> y;
      l = min(l, x - 1);
      d = min(d, y - 1);
      r = max(r, x + 1);
      u = max(u, y + 1);
    }
    vector dis(r - l + 1, vector<int>(u - d + 1, -1));
    for (auto [x, y] : ps) dis[x - l][y - d] = -2;

    int64_t ans[2] {1, 0};
    queue<pair<int, int>> q;
    dis[0 - l][0 - d] = 0; q.emplace(0 - l, 0 - d);
    while (not q.empty()) {
      auto [x, y] = q.front(); q.pop();
      for (int di = 0; di < 4; ++di) {
        int nx = x + dx[di], ny = y + dy[di];
        if (0 <= nx and nx < r - l + 1 and 0 <= ny and ny < u - d + 1 and dis[nx][ny] == -1) {
          dis[nx][ny] = dis[x][y] + 1;
          ans[dis[nx][ny] & 1] += 1;
          if (dis[nx][ny] < S) q.emplace(nx, ny);
        }
      }
    }

    const auto edge = [&](int v) {
      if (v < 0) return;
      ans[0] += S / 2 - v / 2;
      ans[1] += (S + 1) / 2 - (v + 1) / 2;
    };
    const auto corner = [&](int v) {
      if (v < 0) return;
      int t = S - v + 1;
      if (t <= 1) return;
      int64_t t0 = t - (t % 2), t1 = t - (1 - t % 2);
      ans[v % 2] += (1 + t1) * (1 + t1) / 4 - 1;
      ans[1 - v % 2] += (2 + t0) * t0 / 4;
    };
    for (int x = 1; x < r - l; ++x) edge(dis[x][0]), edge(dis[x].back());
    for (int y = 1; y < u - d; ++y) edge(dis[0][y]), edge(dis.back()[y]);
    corner(dis[0][0]); corner(dis[0].back());
    corner(dis.back()[0]); corner(dis.back().back());

    cout << ans[0] << ' ' << ans[1] << '\n';
  }

  return 0;
}
