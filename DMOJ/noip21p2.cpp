#include <bits/stdc++.h>
using namespace std;

const int64_t mod = 998244353;
void modadd(int64_t &u, int64_t v)
{ u += v; if (u >= mod) u -= mod; }

const int kN = 30, kM = 100;
int64_t buf[2][kN + 1][kN + 1][kN + 1];
int n, m, k, v[kM + 1];
int64_t C[kN + 1][kN + 1], vp[kM + 1][kN + 1];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  cin >> n >> m >> k;
  for (int i = 0; i <= m; ++i)
    cin >> v[i];

  C[0][0] = 1;
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= i; ++j) {
      C[i][j] = C[i - 1][j];
      if (j > 0) modadd(C[i][j], C[i - 1][j - 1]);
    }
  for (int i = 0; i <= m; ++i) {
    vp[i][0] = 1;
    for (int j = 1; j <= n; ++j)
      vp[i][j] = vp[i][j - 1] * v[i] % mod;
  }

  auto sc = buf[0], dp = buf[1];
  sc[0][0][0] = 1;

  for (int i = 0; i <= m; ++i) {
    for (int j = 0; j <= n; ++j)
      for (int b = 0; b <= i and b <= k; ++b)
        for (int c = 0; c <= j / 2; ++c) if (sc[j][b][c] != 0) {
          auto &val = sc[j][b][c];
          for (int t = 0; t <= n - j; ++t) {
            if (int nc = c + t; b + nc % 2 <= k)
              modadd(dp[j + t][b + nc % 2][nc / 2],
                  C[n - j][t] * vp[i][t] % mod * val % mod);
          }
          val = 0;
        }
    swap(dp, sc);
  }

  int64_t ans = 0;
  for (int b = 0; b <= k; ++b)
    for (int c = 0; c <= n / 2; ++c)
      if (b + popcount((unsigned)c) <= k)
        ans += sc[n][b][c];

  cout << ans % mod << '\n';

  return 0;
}
