#include <bits/stdc++.h>
using namespace std;

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

  queue<int> q;
  vector<int64_t> dis(N);
  vector<bool> in_q(N);
  const auto spfa = [&](int64_t T, int S) {
    while (not empty(q)) { in_q[q.front()] = false; q.pop(); }
    ranges::fill(dis, LONG_MAX);
    dis[S] = 0, in_q[S] = true, q.push(S);
    while (not empty(q)) {
      int u = q.front(); q.pop(), in_q[u] = false;
      for (auto [v, c, p] : adj[u]) {
        int64_t nd = dis[u] + c + p * T;
        if (nd < dis[v]) {
          dis[v] = nd;
          if (not in_q[v]) q.push(v), in_q[v] = true;
        }
      }
    }
    return dis[S == A ? B : A];
  };

  map<int64_t, int64_t> mp;
  const auto eval = [&](int64_t T) {
    if (mp.count(T)) return mp.at(T);
    return mp[T] = spfa(T, A) + spfa(T, B);
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
