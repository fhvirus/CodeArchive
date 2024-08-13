#include <cstdio>
#include <algorithm>

const int kN = 105;

char g[kN][kN];
int buf[2][kN][2];

void solve() {
  int N;
  scanf("%d\n", &N);
  for (int i = 1; i <= N; ++i)
    fgets(&g[i][1], kN, stdin);

  auto sc = buf[0], dp = buf[1];
  int ans = 3;
  for (int i = 1; i <= N; ++i)
    sc[i][0] = sc[i][1] = 0;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      dp[j][0] = (g[i][j] == 'N' ? sc[j][0] + 1 : 0);
      dp[j][1] = (g[i][j] == 'N' ? sc[j - 1][1] + 1 : 0);
      for (int l = ans + 1; l <= dp[j][0] and l <= dp[j][1] and l <= i and l <= j; ++l)
        if (dp[j - l + 1][0] >= l) ans = l;
    }
    std::swap(dp, sc);
  }

  printf("%d\n", ans <= 3 ? 0 : ans - 3);
}

int main() {
  int T;
  scanf("%d\n", &T);
  while (T --> 0) solve();
}
