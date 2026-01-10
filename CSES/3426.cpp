#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  int64_t x, a, b, c;
  cin >> x >> a >> b >> c;

  int64_t ans = 0;
  for (int i = 1; i <= n; ++i, x = (a * x + b) % c) {
    int t = min({i, n - i + 1, k});
    if (t & 1) ans ^= x;
  }

  cout << ans << '\n';

  return 0;
}
