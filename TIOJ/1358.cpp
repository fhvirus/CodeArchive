#include <cstdio>
int main() {
  int n, ans;
  while (scanf("%d", &n) != EOF) {
    for (ans = 0; n > 1; n = (n + 1) / 2) ans += n - 1;
    printf("%d\n", ans);
  }
  return 0;
}
