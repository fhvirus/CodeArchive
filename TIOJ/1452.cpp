#include <cstdio>
#include <cstdint>

const int kN = 14;
int n, m;
int64_t dp[2][1 << kN];

int64_t solve(int64_t sc[], int j, int k, int l) {
  if (l == m) return sc[k];
  if (j >> l & 1) return solve(sc, j, k, l + 1);
  int64_t res = solve(sc, j, k ^ (1 << l), l + 1);
  if (l + 1 < m and (j >> (l + 1) & 1) == 0)
    res += solve(sc, j, k, l + 2);
  return res;
}

int main() {
  while (scanf("%d %d", &n, &m), n != 0 or m != 0) {
    for (int j = 0; j < (1 << m); ++j) dp[0][j] = (j == 0);
    for (int i = 1; i <= n; ++i) {
      for (int j = 0; j < (1 << m); ++j)
        dp[i & 1][j] = solve(dp[(i & 1) ^ 1], j, 0, 0);
    }
    printf("%ld\n", dp[n & 1][0]);
  }
}
