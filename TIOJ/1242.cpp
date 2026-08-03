#include <bits/stdc++.h>
using namespace std;

const int kN = 1001;
int64_t sum[kN][kN][3];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int R, C;
  cin >> R >> C;
  for (int i = 1; i <= R; ++i)
    for (int j = 1; j <= C; ++j) {
      int64_t* t = sum[i][j];
      cin >> t[0];
      t[1] = t[0] * i;
      t[2] = t[0] * j;
    }

  for (int t : {0, 1})
    for (int i = 1; i <= R; ++i)
      for (int j = 1; j <= C; ++j)
        for (int k : {0, 1, 2})
          sum[i][j][k] += sum[i - t][j - (t ^ 1)][k];
  const auto query = [](int s, int u, int d, int l, int r) {
    return sum[d][r][s] - sum[d][l - 1][s] - sum[u - 1][r][s] + sum[u - 1][l - 1][s]; };

  int q;
  cin >> q;
  for (int u, d, l, r, i = 0; i < q; ++i) {
    cin >> u >> d >> l >> r;
    int64_t ans = 0, tot = query(0, u, d, l, r);

    int m = l - 1;
    for (int b = 1 << __lg(r - l + 1); b > 0; b /= 2)
      if (m + b <= r and query(0, u, d, l, m + b) * 2 < tot)
        m += b;
    ans += query(2, u, d, m + 1, r) - query(2, u, d, l, m) +
      (m + 1) * (query(0, u, d, l, m) - query(0, u, d, m + 1, r));

    m = u - 1;
    for (int b = 1 << __lg(d - u + 1); b > 0; b /= 2)
      if (m + b <= d and query(0, u, m + b, l, r) * 2 < tot)
        m += b;
    ans += query(1, m + 1, d, l, r) - query(1, u, m, l, r) +
      (m + 1) * (query(0, u, m, l, r) - query(0, m + 1, d, l, r));

    cout << ans << '\n';
  }

  return 0;
}
