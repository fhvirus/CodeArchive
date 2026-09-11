#include <bits/stdc++.h>
using namespace std;

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

struct Edge { int u; int64_t c, p; };

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M, A, B, D;
  cin >> N >> M >> A >> B >> D;

  vector adj(N, vector<Edge>());
  for (int u, v, i = 0; i < M; ++i) {
    cin >> u >> v;
    for (int _ : {0, 1}) {
      int64_t c, p; cin >> c >> p;
      adj[u].push_back({v, c, p});
      swap(u, v);
    }
  }

  map<int64_t, int64_t> mp;
  min_heap<pair<int64_t, int>> pq;
  vector<int64_t> dis(N);
  const auto dijkstra = [&](int64_t T, int S) {
    while (not empty(pq)) pq.pop();
    ranges::fill(dis, LONG_MAX);
    pq.emplace(dis[S] = 0, S);
    while (not empty(pq)) {
      auto [d, u] = pq.top(); pq.pop();
      if (d != dis[u]) continue;
      if (u == (S == A ? B : A)) return d;
      for (auto [v, c, p] : adj[u]) {
        int64_t nd = d + c + p * T;
        if (nd < dis[v]) pq.emplace(dis[v] = nd, v);
      }
    }
    return LONG_MAX;
  };
  const auto eval = [&](int64_t T) {
    if (mp.count(T)) return mp.at(T);
    return mp[T] = dijkstra(T, A) + dijkstra(T, B);
  };

  int64_t min_d = eval(0), max_d = eval(D - 1);
  if (min_d > max_d) swap(min_d, max_d);

  int T = 0;
  for (int l = 1 << __lg(D); l > 0; l /= 2)
    if (T + l < D) {
      auto a = eval(T + l - 1), b = eval(T + l);
      if (a <= b) T += l;
      if (a == b) break;
    }

  cout << max(max_d, eval(T)) - min_d << '\n';

  return 0;
}
