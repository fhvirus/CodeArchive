#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  int64_t x, a, b, c;
  cin >> x >> a >> b >> c;

  deque<pair<int64_t, int>> dq;
  int64_t ans = 0;
  for (int i = 1; i <= n; ++i, x = (a * x + b) % c) {
    while (not dq.empty() and dq.back().first >= x)
      dq.pop_back();
    dq.emplace_back(x, i);
    if (i >= k) ans ^= dq.front().first;
    if (dq.front().second <= i - k + 1) dq.pop_front();
  }

  cout << ans << '\n';

  return 0;
}
