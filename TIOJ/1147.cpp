#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> x(n), y(n);
  for (int i = 0; i < n; ++i)
    cin >> x[i] >> y[i];

  tuple<int, int, int> ans(INT_MAX, 0, 0);
  for (int i = 0; i < n; ++i) {
    int cur = 0;
    for (int j = 0; j < n; ++j)
      cur += abs(x[i] - x[j]) + abs(y[i] - y[j]);
    ans = min(ans, make_tuple(cur, x[i], y[i]));
  }

  auto [v, px, py] = ans;
  cout << px << ' ' << py << '\n'
       << v << '\n';

  return 0;
}
