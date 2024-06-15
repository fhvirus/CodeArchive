#include <bits/stdc++.h>
using namespace std;

template <class T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<tuple<int, int, int>> projects(n);
  for (auto &[a, b, p] : projects)
    cin >> a >> b >> p;
  sort(begin(projects), end(projects));
  projects.emplace_back(INT_MAX, INT_MAX, 0);

  min_heap<pair<int, int64_t>> dp;
  dp.emplace(0, 0l);

  int64_t ans = 0;
  for (auto [a, b, p] : projects) {
    while (!dp.empty() and dp.top().first < a) {
      ans = max(ans, dp.top().second);
      dp.pop();
    }
    dp.emplace(b, ans + p);
  }

  cout << ans << '\n';

  return 0;
}
