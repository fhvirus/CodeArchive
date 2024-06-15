#include <bits/stdc++.h>
using namespace std;

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m, k;
  cin >> n >> m >> k;

  vector<vector<pair<int, int>>> adj(n + 1);
  for (int a, b, c, i = 0; i < m; ++i) {
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
  }

  vector dis(n + 1, vector<int64_t>(k, LONG_MAX));
  min_heap<pair<int64_t, int>> pq;
  const auto upd = [&](int u, int64_t d) -> bool {
    bool res = false;
    for (int i = 0; i < k; ++i)
      if (dis[u][i] > d)
        swap(dis[u][i], d), res = true;
    return res;
  };

  dis[1][0] = 0;
  pq.emplace(0l, 1);
  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    int i = (int) (find(begin(dis[u]), end(dis[u]), d) - begin(dis[u]));
    if (i == k) continue;
    for (auto [v, w] : adj[u]) {
      bool r = upd(v, d + w);
      if (r) pq.emplace(d + w, v);
    }
  }

  for (int i = 0; i < k; ++i)
    cout << dis[n][i] << " \n"[i == k - 1];

  return 0;
}
