#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>

const int64_t INF = numeric_limits<int64_t>::max() / 4;
struct MinCostFlow {
  struct Edge { int u, v, rev; int64_t cap, cost, flow; };
  int n;
  vector<vector<Edge>> adj;
  vector<int> seen;
  vector<int64_t> dist, pi;
  vector<Edge*> par;
  MinCostFlow(int _n) : n(_n), adj(n), seen(n), dist(n), pi(n), par(n) {}
  void add_edge(int u, int v, int64_t cap, int64_t cost) {
    if (u == v) return;
    adj[u].push_back({u, v, (int)size(adj[v]), cap, cost, 0});
    adj[v].push_back({v, u, (int)size(adj[u])-1, 0, -cost, 0});
  }
  void path(int s) {
    ranges::fill(seen, 0);
    ranges::fill(dist, INF);
    dist[s] = 0; int64_t di;
    __gnu_pbds::priority_queue<pair<int64_t, int>> q;
    vector<decltype(q)::point_iterator> its(n);
    q.push({0, s});
    while (not empty(q)) {
      s = q.top().second; q.pop();
      seen[s] = 1; di = dist[s] + pi[s];
      for (auto &e : adj[s]) if (not seen[e.v]) {
        int64_t val = di - pi[e.v] + e.cost;
        if (e.cap - e.flow > 0 and val < dist[e.v]) {
          dist[e.v] = val, par[e.v] = &e;
          if (its[e.v] == end(q)) its[e.v] = q.push({-dist[e.v], e.v});
          else q.modify(its[e.v], { -dist[e.v], e.v });
        }
      }
    }
    for (int i = 0; i < n; ++i) pi[i] = min(pi[i] + dist[i], INF);
  }
  auto solve(int s, int t, int64_t lim) {
    int64_t f = 0, c = 0;
    while (path(s), seen[t] and lim > 0) {
      int64_t fi = INF, ci = 0;
      for (Edge* x = par[t]; x; x = par[x->u])
        fi = min(fi, x->cap - x->flow), ci += x->cost;
      if (ci > lim) break;
      fi = min(fi, lim / ci);
      f += fi, c += ci * fi, lim -= ci * fi;
      for (Edge* x = par[t]; x; x = par[x->u]) {
        x->flow += fi;
        adj[x->v][x->rev].flow -= fi;
      }
    }
    return pair(f, c);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M, Z;
  cin >> N >> M >> Z;

  MinCostFlow mcf(N * M * 2 + 2);
  for (int i = 0; i < N; ++i) {
    mcf.add_edge(N * M * 2, (i * M + (M - 1)) * 2, 1, 0);
    mcf.add_edge((i * M + 0) * 2 + 1, N * M * 2 + 1, 1, 1);
  }
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    int k; cin >> k;
    mcf.add_edge((i * M + j) * 2, (i * M + j) * 2 + 1, 1, k);
  }

  const int dir[5] = {1, 0, -1, 0, 1};
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    for (int d : {0, 1, 2, 3})
      if (int ni = i + dir[d], nj = j + dir[d + 1];
          0 <= ni and ni < N and 0 <= nj and nj < M)
        mcf.add_edge((i * M + j) * 2 + 1, (ni * M + nj) * 2, 1, 0);
  }

  auto [f, _] = mcf.solve(N * M * 2, N * M * 2 + 1, Z);
  if (f == 0) cout << "THE ZOMBIES ATE MY BRAIN\n";
  else cout << f << '\n';

  return 0;
}
