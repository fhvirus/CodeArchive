#include <bits/stdc++.h>
using namespace std;

struct Cycle { int a, b, c, pa, pb; };

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vector<vector<int>> adj(N + 1);
  vector<tuple<int, int, int>> es;
  for (int A, B, C, i = 0; i < M; ++i) {
    cin >> A >> B >> C;
    if (C == 0) {
      adj[A].push_back(B);
      adj[B].push_back(A);
    } else es.emplace_back(A, B, C);
  }

  vector<int> par(N + 1), dep(N + 1), id(N + 1), ord;
  const auto dfs = [&](const auto& self, int u) -> void {
    for (int i = 0; i < (int)size(adj[u]); ++i) {
      int &v = adj[u][i];
      if (v == par[u]) swap(v, adj[u].back());
      if (v == par[u]) { adj[u].pop_back(); break; }
      par[v] = u, dep[v] = dep[u] + 1, id[v] = i;
      self(self, v);
    }
    ord.push_back(u);
  };
  dfs(dfs, 1);

  int no = 0, maybe = 0;
  vector<vector<Cycle>> ves(N + 1);
  for (auto [a, b, c] : es) {
    if ((dep[a] + dep[b]) % 2 == 1) no += c;
    else {
      maybe += c;
      if (dep[a] < dep[b]) swap(a, b);
      int u = a, v = b, last = -1;
      while (dep[u] > dep[v])
        last = exchange(u, par[u]);
      if (u == v) {
        ves[v].push_back({b, a, c, last, -1});
        continue;
      }
      while (par[u] != par[v])
        u = par[u], v = par[v];
      ves[par[u]].push_back({b, a, c, u, v});
    }
  }

  vector<vector<int>> without(N + 1);
  for (int u : ord) {
    int s = (int)size(adj[u]);
    vector<int> dp(1 << s, 0);
    for (auto [b, a, c, pa, pb] : ves[u]) {
      pa = id[pa], pb = (pb == -1 ? -1 : id[pb]);
      int em = (1 << pa) | (pb == -1 ? 0 : (1 << pb));

      int sum = c;
      for (int t : {a, b})
        for (int last = -1, i = t; i != u; last = exchange(i, par[i]))
          sum += without[i][last == -1 ? (int)size(adj[i]) : id[last]];

      for (int i = em; i < (1 << s); i = ((i + 1) | em))
        dp[i] = max(dp[i], dp[i ^ em] + sum);
    }

    for (int j = 0; j < s; ++j) {
      int t = without[adj[u][j]].back();
      for (int i = (1 << j); i < (1 << s); i = ((i + 1) | (1 << j)))
        dp[i] = max(dp[i], dp[i ^ (1 << j)] + t);
    }

    auto &w = without[u];
    w.assign(s + 1, 0);
    for (int i = 0; i < s; ++i) w[i] = dp[(1 << s) - 1 - (1 << i)];
    w.back() = dp.back();
  }

  cout << no + (maybe - without[1].back()) << '\n';

  return 0;
}
