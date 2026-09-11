#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n = 2;
  vector<int64_t> f {0, 1, 1};
  for (; f[n-1] - 1 <= INT_MAX; ++n)
    f.push_back(f[n-1] + f[n] - (n % 2 == 0 and n >= 4));

  const auto solve = [&](auto a, auto b) -> int64_t {
    if (a > n) a = n - (a % 2 != n % 2);
    if (b > f[a]) return -1;
    while (a > 2) {
      if (a % 2 == 1 and a >= 5) {
        if (b == f[a-2]) return 3;
        if (b < f[a-2]) a -= 2;
        else { b -= f[a-2] - 1; a -= 1; }
      } else {
        if (b <= f[a-2]) a -= 2;
        else { b -= f[a-2]; a -= 1; }
      }
    }
    return a;
  };

  int T;
  cin >> T;
  while (T --> 0) {
    int64_t a, b;
    cin >> a >> b;
    cout << solve(a, b) << '\n';
  }

  return 0;
}
