#include <bits/stdc++.h>
using namespace std;

const int dir[5] = {1, 0, -1, 0, 1};
const int diag[5] = {1, -1, -1, 1, 1};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int m, n;
  cin >> m >> n;

  vector<string> g(m);
  for (auto &i : g) cin >> i;

  vector<bool> vis(m * n * 4);
  const auto get_id = [&](int i, int j, int d) {
    return (i * n + j) * 4 + d; };
  const auto ok = [&](int i, int j) {
    return 0 <= i and i < m and 0 <= j and j < n and g[i][j] != '#'; };

  vector<tuple<int, int, int>> cur, nxt;
  vis[get_id(0, 0, 0)] = 1;
  cur.emplace_back(0, 0, 0);

  for (int t = 0; not empty(cur); ++t) {
    nxt.clear();
    const auto enqueue = [&](int i, int j, int d) {
      if (int id = get_id(i, j, d); not vis[id])
        vis[id] = 1, nxt.emplace_back(i, j, d);
    };

    for (auto [i, j, d] : cur) {
      if (i == m - 2 and j == n - 1 and d == 0) {
        cout << t << '\n';
        exit(0);
      }

      // Go
      if (ok(i + dir[d] * 2, j + dir[d + 1] * 2))
        enqueue(i + dir[d], j + dir[d + 1], d);
      // Rotate 1 90
      if (int nd = (d + 1) % 4;
          ok(i + diag[d], j + diag[d + 1]) and
          ok(i + dir[nd], j + dir[nd + 1]))
        enqueue(i, j, nd);
      // Rotate 1 -90
      if (int nd = (d + 3) % 4;
          ok(i + diag[nd], j + diag[nd + 1]) and
          ok(i + dir[nd], j + dir[nd + 1]))
        enqueue(i, j, nd);
      // Rorate 0 -90
      if (int nd = (d + 1) % 4;
          ok(i + dir[nd], j + dir[nd + 1]) and
          ok(i + diag[d], j + diag[d + 1]))
        enqueue(i + diag[d], j + diag[d + 1], (d + 3) % 4);
      // Rorate 0 90
      if (int nd = (d + 3) % 4;
          ok(i + dir[nd], j + dir[nd + 1]) and
          ok(i + diag[nd], j + diag[nd + 1]))
        enqueue(i + diag[nd], j + diag[nd + 1], (d + 1) % 4);
    }
    nxt.swap(cur);
  }

  cout << "No Way!\n";
  return 0;
}
