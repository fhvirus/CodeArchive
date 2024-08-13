#include <cstdio>

int main() {
  const int kN = 51;
  int ans[kN];
  ans[1] = 1;
  for (int i = 2; i < kN; ++i) {
    ans[i] = 3 * (1 << 25);
    for (int j = i > 25 ? i - 25 : 1; j < i; ++j) {
      int t = 2 * ans[j] + (1 << (i - j)) - 1;
      if (ans[i] > t) ans[i] = t;
    }
  }

  int T, n;
  scanf("%d", &T);
  while (T --> 0) {
    scanf("%d", &n);
    printf("%d\n", ans[n]);
  }
  return 0;
}
