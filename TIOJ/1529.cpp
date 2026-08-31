#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  typedef double T;

  int n;
  cin >> n;

  vector<pair<T, T>> b(n);
  for (auto &[t, w] : b) cin >> w >> t;
  ranges::sort(b);

  T cur_t = 0, ans = 0;
  priority_queue<pair<T, T>> pq;
  for (auto [t, w] : b) {
    cur_t += w;
    pq.emplace(w, 1);
    while (cur_t > t) {
      auto [v, q] = pq.top(); pq.pop();
      T take = min(q, (cur_t - t) / v);
      q -= take, cur_t -= take * v, ans += take;
      if (q > 0) pq.emplace(v, q);
    }
  }

  cout << setprecision(3) << fixed << ans * 100 << '\n';

  return 0;
}
