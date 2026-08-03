#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int dfs(int x, int y, int ex, int ey, int dep, bool hit, auto& vis) {
  if (x == ex and y == ey) return (dep == 0);
  bool side = (min(x, y) == 1 or max(x, y) == (int)size(vis) - 2);

  int ans = 0, can = 0b1111;
  for (int d = 0; d < 4; ++d) {
    int nx = x + dx[d], ny = y + dy[d];
    if (vis[nx][ny]) can &= ~(1 << d);
    else if (vis[nx + dx[d]][ny + dy[d]]) { // if hit wall
      bool a = vis[nx + dx[d ^ 2]][ny + dy[d ^ 2]];
      bool b = vis[nx + dx[d ^ 3]][ny + dy[d ^ 3]];
      if (hit and not a and not b) can &= ~(1 << d); // two disconnected block
      if ((a ^ b) and not (nx == ex and ny == ey)) // otherwise dead end
        can &= (1 << d);
    }
  }

  vis[x][y] = true;
  for (int d = 0; d < 4; ++d) if (can >> d & 1)
    ans += dfs(x + dx[d], y + dy[d], ex, ey, dep - 1, hit or side, vis);
  vis[x][y] = false;

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, sx, sy, ex, ey;
  map<tuple<int, int, int>, int> mp;
  while (cin >> N >> sx >> sy >> ex >> ey) {
    int ps = (sx + sy) % 2, pe = (ex + ey) % 2;
    if ((N % 2 == 1 and (ps != 0 or pe != 0)) or
        (N % 2 == 0 and (ps == pe)) or
        (sx == ex and sy == ey and N > 1)) {
      cout << 0 << '\n';
      continue;
    }
    {
      tuple<int, int, int, int> a(sx, sy, ex, ey);
      for (int r = 0; r < 4; ++r) {
        for (int f : {0, 1}) {
          a = min(a, tuple(sx, sy, ex, ey));
          a = min(a, tuple(ex, ey, sx, sy));
          swap(sx, sy), swap(ex, ey);
        }
        tie(sx, sy) = pair(sy, -sx + (1 - -N));
        tie(ex, ey) = pair(ey, -ex + (1 - -N));
      }
      tie(sx, sy, ex, ey) = a;
    }

    tuple<int, int, int> key(N, (sx - 1) * N + (sy - 1),
        (ex - 1) * N + (ey - 1));
    if (mp.count(key)) {
      cout << mp.at(key) << '\n';
      continue;
    }

    vector vis(N + 2, vector<bool>(N + 2));
    for (int i = 0; i <= N + 1; ++i) {
      vis[i][0] = vis[i][N + 1] = true;
      vis[0][i] = vis[N + 1][i] = true;
    }
    cout << (mp[key] = dfs(sx, sy, ex, ey, N * N - 1, false, vis)) << '\n';
  }

  return 0;
}
