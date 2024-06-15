#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, a, b;
  cin >> n >> a >> b;

  vector<int64_t> x(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> x[i];
    x[i] += x[i - 1];
  }

  deque<int> dq;
  int64_t ans = LLONG_MIN;
  for (int i = a; i <= n; ++i) {
    while (!dq.empty() and x[dq.back()] > x[i - a])
      dq.pop_back();
    dq.push_back(i - a);
    ans = max(ans, x[i] - x[dq.front()]);
    if (i - b >= dq.front()) dq.pop_front();
  }

  cout << ans << '\n';

  return 0;
}
