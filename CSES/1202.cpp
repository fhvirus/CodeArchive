#include <bits/stdc++.h>
using namespace std;

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int MOD = 1e9 + 7;

  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, int>>> adj(n + 1);
  for (int a, b, c, i = 0; i < m; ++i) {
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
  }

  vector<int64_t> dis(n + 1, LONG_MAX);
  vector<int> cnt(n + 1), mnf(n + 1, INT_MAX), mxf(n + 1, INT_MIN);
  min_heap<pair<int64_t, int>> pq;

  dis[1] = 0l, cnt[1] = 1, mnf[1] = mxf[1] = 0;
  pq.emplace(dis[1], 1);

  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d != dis[u]) continue;
    for (auto [v, w] : adj[u]) {
      if (dis[v] > d + w) {
        dis[v] = d + w;
        cnt[v] = 0;
        mnf[v] = INT_MAX;
        mxf[v] = INT_MIN;
        pq.emplace(dis[v], v);
      }
      if (dis[v] == d + w) {
        cnt[v] += cnt[u];
        cnt[v] -= MOD * (cnt[v] >= MOD);
        mnf[v] = min(mnf[v], mnf[u] + 1);
        mxf[v] = max(mxf[v], mxf[u] + 1);
      }
    }
  }

  cout << dis[n] << ' ' << cnt[n] << ' ' << mnf[n] << ' ' << mxf[n] << '\n';

  return 0;
}
