#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int INF = 8e7;

  for (int n, m; cin >> n >> m, n or m; ) {
    vector<string> g(m);
    for (auto &i : g) cin >> i;

    vector<int> need(m * n);
    for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j)
      need[i * n + j] = (g[i][j] == 'o');

    vector dis(m * n, vector<int>(m * n, INF)), par = dis;
    for (int si = 0; si < m; ++si) for (int sj = 0; sj < n; ++sj) if (g[si][sj] != '#') {
      deque<pair<int, int>> dq;
      vector<bool> vis(m * n);
      int s = si * n + sj;
      auto &d = dis[s], &p = par[s];
      d[s] = need[s], p[s] = s;
      dq.emplace_back(si, sj);
      while (not empty(dq)) {
        auto [i, j] = dq.front(); dq.pop_front();
        int u = i * n + j;
        if (vis[u]) continue;
        vis[u] = true;
        for (auto [ni, nj] : vector<pair<int, int>> {{i + 1, j}, {i - 1, j}, {i, j + 1}, {i, j - 1}})
          if (0 <= ni and ni < m and 0 <= nj and nj < n and g[ni][nj] != '#')
            if (int v = ni * n + nj; d[v] > d[u] + need[v]) {
              d[v] = d[u] + need[v];
              p[v] = u;
              if (need[v]) dq.emplace_back(ni, nj);
              else dq.emplace_front(ni, nj);
            }
      }
    }

    vector<int> homes;
    for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j)
      if (isupper(g[i][j])) homes.push_back(i * n + j);

    tuple<int, int, int> best(INF, -1, -1);
    for (int a = 0; a < m * n; ++a) if (g[a / n][a % n] != '#')
      for (int b = a; b < m * n; ++b) if (g[b / n][b % n] != '#') {
        int tot = dis[a][b];
        for (int h : homes) tot += min(dis[h][a] - need[a], dis[h][b] - need[b]);
        auto cur = make_tuple(tot, a, b);
        best = min(best, cur);
      }

    const auto plow = [&](int u, int v) {
      while (u != v) {
        if (need[v]) g[v / n][v % n] = '.';
        v = par[u][v];
      }
    };
    auto [tot, a, b] = best;
    plow(a, b);
    for (int h : homes) plow(h, dis[h][a] - need[a] < dis[h][b] - need[b] ? a : b);

    cout << n << ' ' << m << '\n';
    for (auto i : g) cout << i << '\n';
    cout << '\n';
  }
  cout << "0 0\n";

  return 0;
}
