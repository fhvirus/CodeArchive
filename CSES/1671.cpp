#include <bits/stdc++.h>
using namespace std;

template<class T>
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
  min_heap<pair<int64_t, int>> pq;

  dis[1] = 0;
  pq.emplace(dis[1], 1);

  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d != dis[u]) continue;
    for (auto [v, w] : adj[u]) {
      if (d + w < dis[v])
        pq.emplace(dis[v] = d + w, v);
    }
  }

  for (int i = 1; i <= n; ++i)
    cout << dis[i] << " \n"[i == n];

  return 0;
}
