#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  vector<double> dp(1 << n), sc(1 << n);
  sc[(1 << n) - 1] = 1;

  for (int i, j, k = 0; k < m; ++k) {
    double p;
    cin >> i >> j >> p;
    i -= 1, j -= 1;
    ranges::fill(dp, 0);
    for (int a = 0; a < (1 << n); ++a) {
      if ((a >> i & 1) and (a >> j & 1)) {
        dp[a] += sc[a] * (1 - p);
        dp[a ^ (1 << j)] += sc[a] * p;
      } else dp[a] += sc[a];
    }
    swap(dp, sc);
  }

  cout << setprecision(10) << fixed;
  for (int i = 0; i < n; ++i) {
    double p = 0;
    for (int a = 0; a < (1 << n); ++a)
      if (a >> i & 1) p += sc[a];
    cout << p << '\n';
  }

  return 0;
}

