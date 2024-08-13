// keyword: stable marriage, gale-shapley algorithm
#include <cstdio>

const int kN = 101;
int n, a[kN][kN], b[kN][kN], ma[kN], mb[kN], it[kN], q[kN];

int main() {
  while (scanf("%d", &n) != EOF) {
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; ++i) {
      for (int j = 1, v; j <= n; ++j) {
        scanf("%d", &v);
        b[i][v] = j;
      }
    }
    for (int i = 1; i <= n; ++i) ma[i] = 0;
    for (int i = 1; i <= n; ++i) mb[i] = 0;
    for (int i = 1; i <= n; ++i) it[i] = 0;

    for (int i = 1; i <= n; ++i) q[i] = i;
    for (int t = n; t > 0; ) {
      int i = q[t--];
      int j = a[i][++it[i]];
      if (mb[j] == 0 or b[j][i] < b[j][mb[j]]) {
        if (mb[j] != 0) q[++t] = mb[j];
        ma[mb[j]] = 0;
        ma[i] = j;
        mb[j] = i;
      } else ++t;
    }

    for (int i = 1; i <= n; ++i)
      printf("#%d match to #%d\n", i, ma[i]);
  }
  return 0;
}
