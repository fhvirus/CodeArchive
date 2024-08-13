#include <cstdio>

int main() {
  int N;
  scanf("%d", &N);

  int cnt = 0;
  int ans[100];

  for (int res, i = 1; i <= N; i += 4) {
    printf("? %d", (i + 4 <= N ? 4 : N - i + 1));
    for (int j = i; j <= N and j < i + 4; ++j)
      printf(" %d", j);
    printf("\n");
    fflush(stdout);

    scanf("%d", &res);
    if (res) {
      for (int j = i; j <= N and j < i + 4; ++j) {
        printf("? 1 %d\n", j);
        fflush(stdout);
        scanf("%d", &res);
        if (res) ans[cnt++] = j;
      }
    }
  }

  printf("! %d", cnt);
  for (int i = 0; i < cnt; ++i)
    printf(" %d", ans[i]);
  printf("\n");
  fflush(stdout);
}
