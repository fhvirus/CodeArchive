#include <bits/stdc++.h>
using namespace std;

struct Graph {
  int en; vector<int> to, nxt, head;
  Graph(int n, int m) : en(0), to(m, -1), nxt(m, -1), head(n, -1) {}
  void add_edge(int u, int v) { to[en] = v; nxt[en] = head[u]; head[u] = en++; }
  struct It {
    const Graph* g; int e;
    int operator * () const { return g->to[e]; }
    It& operator ++ () { e = g->nxt[e]; return *this; }
    bool operator != (const It& o) const { return e != o.e; }
  };
  struct Range {
    const Graph* g; int u;
    It begin() const { return {g, g->head[u]}; }
    It end()   const { return {g, -1}; }
  };
  Range adj(int u) const { return {this, u}; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  Graph g(N, M * 2);

  for (int u, v, i = 0; i < M; ++i) {
    cin >> u >> v;
    g.add_edge(u, v);
    g.add_edge(v, u);
  }

  vector w(N, array<int64_t, 3>{0, 0, 0});
  const auto upd = [&](auto& w_u, auto& w_v, int64_t mul = 1) {
    w_u[0] += mul * w_v[0];
    w_u[1] += mul * (w_v[0] + w_v[1]);
    w_u[2] += mul * (w_v[0] + 2 * w_v[1] + w_v[2]);
  };
  const auto dfs1 = [&](const auto& self, int u, int p) -> void {
    w[u][0] = 1;
    for (int v : g.adj(u)) if (v != p) {
      self(self, v, u);
      upd(w[u], w[v]);
    }
  };
  const auto dfs2 = [&](const auto& self, int u, int p) -> pair<int64_t, int> {
    pair<int64_t, int> best(w[u][2], u);
    for (int v : g.adj(u)) if (v != p) {
      auto w_u = w[u];
      upd(w_u, w[v], -1);
      upd(w[v], w_u);
      best = min(best, self(self, v, u));
    }
    return best;
  };

  vector<pair<int, int>> head;
  for (int i = 0; i < N; ++i) if (w[i][0] == 0) {
    dfs1(dfs1, i, i);
    auto [_, h] = dfs2(dfs2, i, i);
    head.emplace_back(h, w[i][0]);
  }

  ranges::sort(head);
  for (auto [h, s] : head)
    cout << h << ' ' << s << '\n';

  return 0;
}
