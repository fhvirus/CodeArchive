#include <bits/stdc++.h>
using namespace std;

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n, m; cin >> n >> m; ) {
    vector adj(n, vector<pair<int, int>>());
    for (int a, b, d, i = 0; i < m; ++i) {
      cin >> a >> b >> d;
      adj[a].emplace_back(b, d);
      adj[b].emplace_back(a, d);
    }

    int st, ed;
    cin >> st >> ed;

    const int INF = INT_MAX / 2;
    vector<array<int, 2>> dis(n, {INF, INF});
    min_heap<pair<int, int>> pq;

    dis[st][0] = 0, pq.emplace(0, st);
    while (not empty(pq)) {
      auto [d, u] = pq.top(); pq.pop();
      if (d != dis[u][0] and d != dis[u][1]) continue;
      for (auto [v, w] : adj[u]) {
        int t = d + w;
        if (t < dis[v][0]) {
          pq.emplace(t, v);
          swap(t, dis[v][0]);
          dis[v][1] = t;
        } else if (t > dis[v][0] and t < dis[v][1]) {
          pq.emplace(t, v);
          dis[v][1] = t;
        }
      }
    }

    cout << (dis[ed][1] == INF ? -1 : dis[ed][1]) << '\n';
  }

  return 0;
}
