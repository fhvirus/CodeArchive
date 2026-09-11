#include <bits/stdc++.h>
using namespace std;

const int kN = 3000, kM = 1000, mod = 100000007;
int C[kN + 1][kM + 1];
int64_t sum[kM];

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int i = 0; i <= kN; ++i) {
    C[i][0] = 1;
    if (i <= kM) C[i][i] = 1;
    for (int j = 1; j < min(i, kM + 1); ++j) {
      C[i][j] = C[i-1][j] + C[i-1][j-1];
      if (C[i][j] >= mod) C[i][j] -= mod;
    }
  }
  sum[0] = 1;
  for (int i = 1; i < kM; ++i) {
    sum[i] = sum[i - 1] + C[kN][i];
    if (sum[i] >= mod) sum[i] -= mod;
  }

  for (int n; cin >> n; ) {
    int64_t ans = sum[n - 1];
    for (int k, last = 0, i = 0; i < n; ++i) {
      cin >> k;
      ans += C[kN - last][n - i] - C[kN + 1 - k][n - i] + mod;
      last = k;
    }
    cout << ans % mod << '\n';
  }

  return 0;
}
