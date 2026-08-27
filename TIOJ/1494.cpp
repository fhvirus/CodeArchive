#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int64_t mod = 1e9 + 7;

  int64_t i, j;
  cin >> i >> j;

  int64_t t = gcd(i + 1, j + 1), a = 0, b = 1;
  for (auto l = __lg(t); l >= 0; --l) {
    tie(a, b) = pair(
        a * (2 * b - a + mod) % mod,
        (a * a + b * b) % mod);
    if (t >> l & 1) tie(a, b) = pair(b, a + b);
  }

  cout << a << '\n';

  return 0;
}
