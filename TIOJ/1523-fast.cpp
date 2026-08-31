#include <bits/stdc++.h>
using namespace std;

template <class T> void chmin(T &a, T b) { if (a > b) a = b; }

struct Ship {
  int u, p, d, c;
  vector<int> len;
};

optional<Ship> get_ship(int n, const auto& g) {
  int u = 0, p, d, c = -1;
  vector<int> len;
  while (g[u].find('r') == string::npos) ++u;
  for (p = d = u; d < n; ++d) {
    auto l = g[d].find('r');
    if (l == string::npos) break;
    auto r = g[d].find_first_not_of('r', l);
    r = (r == string::npos ? n - 1 : r - 1);
    if ((r - l + 1) % 2 == 0 or (c != -1 and (int) (r + l) / 2 != c))
      return nullopt;
    c = (int) (r + l) / 2;
    len.push_back((int)r - c);
    if (len[p - u] < len.back()) p = d;
  }
  u -= p, d -= p + 1;
  return Ship {u, p, d, c, len};
}

auto get_bad(int n, const auto& g, const auto& ship) {
  vector bad(n, vector<int>(n));
  for (int c = 0; c < n; ++c) {
    vector<int> xs;
    for (int r = 0; r < n; ++r)
      if (g[r][c] == 'X') xs.push_back(r);
    for (int pr = 0, xi = -1; pr < n; ++pr) {
      if (xi + 1 < (int)size(xs) and xs[xi + 1] <= pr) ++xi;
      int len = -1;
      if (0 <= xi and pr + ship.u <= xs[xi])
        len = ship.len[xs[xi] - (pr + ship.u)];
      if (xi + 1 < (int)size(xs) and xs[xi + 1] <= pr + ship.d)
        len = max(len, ship.len[xs[xi + 1] - (pr + ship.u)]);
      if (len == -1) continue;
      bad[pr][max(0, c - len)] += 1;
      if (int r = c + len + 1; r < n)
        bad[pr][r] -= 1;
    }
  }
  for (auto &i : bad) partial_sum(begin(i), end(i), begin(i));
  return bad;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<string> g(n);
  for (auto &i : g) cin >> i;

  Ship ship;
  if (auto r = get_ship(n, g)) ship = *r;
  else {
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < i; ++j)
        swap(g[i][j], g[j][i]);
    ship = *get_ship(n, g);
  }

  auto bad = get_bad(n, g, ship);

  const int INF = INT_MAX / 2;
  int ship_to_corner[2] = {INF, INF};
  for (int i = ship.u - 1; i <= ship.d + 1; ++i) {
    int l = (ship.u <= i and i <= ship.d ? ship.len[i - ship.u] : 0);
    chmin(ship_to_corner[i >= 0], l + abs(i) + 1);
    if (i == 0) chmin(ship_to_corner[0], l + 1);
  }
  const auto get_escape_dis = [&](int i, int j) {
    bool bj = (j == 0 or j == n - 1);
    int res = INF;
    if (bj) chmin(res, ship.len[-ship.u] + 1);
    if (i == 0) chmin(res, abs(ship.d) + 1);
    if (i == n-1) chmin(res, abs(ship.u) + 1);
    if ((i == 0 or i == n-1) and bj)
      chmin(res, ship_to_corner[i == 0]);
    return res;
  };

  int ans = INF;

  const int dir[5] = {1, 0, -1, 0, 1};
  vector<pair<int, int>> cur, nxt;
  bad[ship.p][ship.c] = 1;
  cur.emplace_back(ship.p, ship.c);
  for (int dis = 0; not empty(cur); ++dis) {
    nxt.clear();
    for (auto [i, j] : cur) {
      if (min(i, j) == 0 or max(i, j) == n - 1)
        chmin(ans, dis + get_escape_dis(i, j));
      for (int d : {0, 1, 2, 3}) {
        int ni = i + dir[d], nj = j + dir[d + 1];
        if (0 <= min(ni, nj) and max(ni, nj) < n and bad[ni][nj] == 0)
          bad[ni][nj] = 1, nxt.emplace_back(ni, nj);
      }
    }
    swap(cur, nxt);
  }

  if (ans == INF) cout << "impossible\n";
  else cout << ans << '\n';

  return 0;
}
