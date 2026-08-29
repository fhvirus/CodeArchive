#include <bits/stdc++.h>
using namespace std;

template <class T> void chmin(T &a, T b) { if (a > b) a = b; }

const int kN = 2000;
typedef bitset<kN * 3> row;
const row all_1 = row().set();

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int INF = INT_MAX / 2;

  int n;
  cin >> n;

  vector<string> g(n);
  for (auto &i : g) cin >> i;

  int boat_u = -1, boat_d = -1, boat_l = INF, boat_r = -INF;
  vector<pair<int, int>> boat_lr;
  for (int i = 0; i < n; ++i) {
    auto l = g[i].find('r');
    if (l == string::npos) {
      if (boat_u == -1) continue;
      break;
    }
    if (boat_u == -1) boat_u = i;
    boat_d = i;
    auto r = g[i].find_first_not_of('r', l);
    if (r == string::npos) r = n;
    boat_lr.emplace_back(l, r - 1);
  }
  int boat_cx = max(boat_lr[0].first, boat_lr.back().first), boat_cy = -1;
  for (int i = boat_u; i <= boat_d; ++i) {
    auto [l, r] = boat_lr[i - boat_u];
    if (r - l > boat_r - boat_l)
      boat_l = l, boat_r = r, boat_cy = i;
  }
  boat_u -= boat_cy, boat_d -= boat_cy;
  boat_l -= boat_cx, boat_r -= boat_cx;
  int boat_to_corner[2][2] = {{INF, INF}, {INF, INF}};
  for (int i = 0; i <= boat_d - boat_u; ++i) {
    auto &[l, r] = boat_lr[i];
    l -= boat_cx, r -= boat_cx;
    chmin(boat_to_corner[boat_u + i >= 0][0], abs(l) + abs(boat_u + i) + 1);
    chmin(boat_to_corner[boat_u + i >= 0][1], abs(r) + abs(boat_u + i) + 1);
  }
  for (int t : {0, 1}) chmin(boat_to_corner[0][t], -boat_u + 1);
  for (int t : {0, 1}) chmin(boat_to_corner[1][t], boat_d + 1);
  for (int t : {0, 1}) chmin(boat_to_corner[t][0], -boat_l + 1);
  for (int t : {0, 1}) chmin(boat_to_corner[t][1], boat_r + 1);

  vector<row> no_boat(n), row_ok(n);
  for (int i = 0; i < n; ++i) {
    for (auto &r : row_ok) r.reset();
    row_ok[n - 1].set(0);
    for (int j = 0; j < n and g[i][j] != 'X'; ++j) row_ok[n - 1].set(j - (n - 1) + n);
    row_ok[n - 1] |= (all_1 << (n + n));

    for (int l = 0, r = 0; l < n; l = r) {
      r = l + 1;
      if (g[i][l] == 'X') continue;
      for (; r < n and g[i][r] != 'X'; ++r);
      if (r < n) row_ok[r - l - 1].set(l + n);
      else row_ok[n - 1] |= (all_1 << (l + n));
    }

    for (int len = n - 1; len >= 1; --len)
      row_ok[len - 1] |= (row_ok[len] << 1) | row_ok[len];

    for (int bj = boat_u; bj <= boat_d; ++bj) if (0 <= i - bj and i - bj < n) {
      auto [l, r] = boat_lr[bj - boat_u];
      no_boat[i - bj] |= ~row_ok[r - l] >> (n + l);
    }
  }

  int ans = INF;

  const int dir[5] = {1, 0, -1, 0, 1};
  vector<pair<int, int>> cur, nxt;
  no_boat[boat_cy][boat_cx] = 1;
  cur.emplace_back(boat_cy, boat_cx);
  for (int dis = 0; not empty(cur); ++dis) {
    nxt.clear();
    for (auto [i, j] : cur) {
      if (min(i, j) == 0 or max(i, j) == n - 1) {
        if (i == 0) chmin(ans, dis + boat_d + 1);
        if (i == n - 1) chmin(ans, dis + -boat_u + 1);
        if (j == 0) chmin(ans, dis + boat_r + 1);
        if (j == n - 1) chmin(ans, dis + -boat_l + 1);
        if ((i == 0 or i == n - 1) and (j == 0 or j == n - 1))
          chmin(ans, dis + boat_to_corner[i == 0][j == 0]);
      }
      for (int d : {0, 1, 2, 3}) {
        int ni = i + dir[d], nj = j + dir[d + 1];
        if (0 <= min(ni, nj) and max(ni, nj) < n and not no_boat[ni][nj])
          no_boat[ni][nj] = 1, nxt.emplace_back(ni, nj);
      }
    }
    swap(cur, nxt);
  }

  if (ans == INF) cout << "impossible\n";
  else cout << ans << '\n';
  return 0;
}
