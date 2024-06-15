#include <bits/stdc++.h>
using namespace std;

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, int>>> adj(n + 1);
  for (int a, b, c, i = 0; i < m; ++i) {
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
  }

  vector<int64_t> dis(n + 1, LONG_MAX);
  dis[1] = 0;

  min_heap<pair<int64_t, int>> pq;
  pq.emplace(dis[1], 1);

  const auto dijkstra = [&]() -> void {
    while (!pq.empty()) {
      auto [d, u] = pq.top(); pq.pop();
      if (d != dis[u]) continue;
      for (auto [v, w] : adj[u]) if (dis[v] > d + w) {
        dis[v] = d + w;
        pq.emplace(dis[v], v);
      }
    }
  };

  dijkstra();
  auto ndis = dis;
  for (int u = 1; u <= n; ++u) {
    for (auto [v, w] : adj[u]) if (dis[v] > ndis[u] + w / 2) {
      dis[v] = ndis[u] + w / 2;
      pq.emplace(dis[v], v);
    }
  }
  dijkstra();

  cout << dis[n] << '\n';

  return 0;
}
