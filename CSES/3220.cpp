#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  int64_t x, a, b, c;
  cin >> x >> a >> b >> c;

  int64_t sum = 0, l = x, r = x;
  for (int i = 1; i <= k; ++i, r = (a * r + b) % c)
    sum += r;

  int64_t ans = 0;
  for (int i = k; i <= n; ++i) {
    ans ^= sum;
    sum += r - l;
    l = (a * l + b) % c;
    r = (a * r + b) % c;
  }

  cout << ans << '\n';

  return 0;
}
