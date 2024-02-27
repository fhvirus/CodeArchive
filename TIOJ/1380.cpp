// 這題的題敘不知道在幹嘛……
// 給你一張圖，你要從任意點開始造訪每一個點，請問能不能在長度 d 以內的路徑（不用簡單）完成？
#include <cstdio>
#define chmin(a, b) (a = (a > b ? b : a))

const int kN = 20;
int n, m, d;
short w[kN][kN];
short dp[1 << kN][kN];

int main() {

  while (scanf("%d%d%d", &n, &m, &d) != EOF) {
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        w[i][j] = d + 1;

    for (int u, v, c, i = 0; i < m; ++i) {
      scanf("%d%d%d", &u, &v, &c);
      w[u][v] = chmin(w[v][u], c);
    }
    for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          chmin(w[i][j], w[i][k] + w[k][j]);

    for (int i = 0; i < (1 << n); ++i)
      for (int j = 0; j < n; ++j)
        dp[i][j] = d + 1;
    for (int i = 0; i < n; ++i) dp[1 << i][i] = 0;

    for (int i = 1; i < (1 << n); ++i) {
      for (int j = 0; j < n; ++j) {
        if ((i >> j & 1) == 0 or dp[i][j] > d) continue;
        for (int k = 0; k < n; ++k) {
          if (i >> k & 1) continue;
          chmin(dp[i | (1 << k)][k], dp[i][j] + w[j][k]);
        }
      }
    }

    bool ans = false;
    for (int i = 0; i < n; ++i)
      ans |= (dp[(1 << n) - 1][i] <= d);
    puts(ans ? "OK" : "...");
  }

  return 0;
}
