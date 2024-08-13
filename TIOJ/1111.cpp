#include <cstdio>

const int kN = 505;

int N;
char g[kN][kN];
int ans[128];

int main() {
  while (scanf("%d\n", &N), N != 0) {
    for (int i = 1; i <= N; ++i)
      fgets(&g[i][1], kN, stdin);
    for (int i = 0; i <= N + 1; ++i)
      g[N+1][i] = g[i][N + 1] = 0;
    ans['A'] = ans['B'] = ans['C'] = 0;

    // horizontal
    for (int i = 1; i <= N; ++i) {
      char cur = '.';
      int cnt = 0;
      for (int j = 1; j <= N + 1; ++j) {
        if (g[i][j] != cur) {
          ans[cur] += (cnt == 5);
          cur = g[i][j];
          cnt = 0;
        }
        cnt += 1;
      }
    }

    // vertical
    for (int j = 1; j <= N; ++j) {
      char cur = '.';
      int cnt = 0;
      for (int i = 1; i <= N + 1; ++i) {
        if (g[i][j] != cur) {
          ans[cur] += (cnt == 5);
          cur = g[i][j];
          cnt = 0;
        }
        cnt += 1;
      }
    }

    // diagonal
    for (int i = N, j = 1; j != N + 1; i == 1 ? ++j : --i) {
      char cur = '.';
      int cnt = 0;
      for (int d = 0; i + d <= N + 1 and j + d <= N + 1; ++d) {
        if (g[i + d][j + d] != cur) {
          ans[cur] += (cnt == 5);
          cur = g[i + d][j + d];
          cnt = 0;
        }
        cnt += 1;
      }
    }

    // anti-diagonal
    for (int i = 1, j = 1; i != N + 1; j == N ? ++i : ++j) {
      char cur = '.';
      int cnt = 0;
      for (int d = 0; i + d <= N + 1 and j - d >= 0; ++d) {
        if (g[i + d][j - d] != cur) {
          ans[cur] += (cnt == 5);
          cur = g[i + d][j - d];
          cnt = 0;
        }
        cnt += 1;
      }
    }

    printf("A %d\n", ans['A']);
    printf("B %d\n", ans['B']);
    printf("C %d\n", ans['C']);
    puts("");
  }
}
