#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  typedef double T;

  int m, n; T k;
  cin >> m >> n >> k;

  vector a(m, vector<T>(n));
  for (auto &i : a) for (auto &j : i) cin >> j;

  auto b = a;
  for (int i = 1; i < m; ++i)
    for (int j = 0; j < n; ++j)
      b[i][j] = a[i][j] + b[i - 1][j] / k;

  vector<T> tmp(n);
  for (int i = m - 1; i >= 0; --i)
    for (int j = 0; j < n; ++j) {
      b[i][j] += tmp[j] / k;
      tmp[j] = a[i][j] + tmp[j] / k;
    }

  T ans = -1e18;
  for (int i = 0; i < m; ++i) {
    tmp[n - 1] = 0;
    for (int j = n - 1; j > 0; --j)
      tmp[j - 1] = (b[i][j] + tmp[j]) / k;

    T cur = 0;
    for (int j = 0; j < n; ++j) {
      cur = cur / k + b[i][j];
      ans = max(ans, cur + tmp[j]);
    }
  }

  cout << setprecision(3) << fixed << ans << '\n';

  return 0;
}
