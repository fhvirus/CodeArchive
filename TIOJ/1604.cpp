#include <bits/stdc++.h>
using namespace std;

template <class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
struct Event {
  int t, i, j, d;
  auto operator > (const Event& o) const { return t > o.t; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int s, e, m, a, b;
  cin >> s >> e >> m >> a >> b;

  vector<int> k(m * (a + b));
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < a + b; ++j)
      cin >> k[i * (a + b) + j];

  vector<int> dis(m, INT_MIN);
  min_heap<Event> pq;
  for (int j = 0; j < a; ++j) pq.push({k[0 * (a + b) + j], 0, j, 0});
  for (int j = a; j < a + b; ++j) pq.push({k[(m - 1) * (a + b) + j], m - 1, j, INT_MIN});

  while (not empty(pq)) {
    auto [t, i, j, d] = pq.top(); pq.pop();
    if (t > e) break;
    if (t >= s) dis[i] = max(dis[i], d);
    if (j < a) {
      if (i + 1 < m) {
        int v = (i + 1) * (a + b) + j;
        pq.push({k[v], i + 1, j, t < s ? dis[i + 1] : dis[i] + (k[v] - t)});
      }
    } else {
      if (i > 0) {
        int v = (i - 1) * (a + b) + j;
        pq.push({k[v], i - 1, j, t < s ? dis[i - 1] : dis[i] + (k[v] - t)});
      }
    }
  }

  cout << (e - s) - dis[0] << '\n';

  return 0;
}
