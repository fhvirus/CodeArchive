#include <cstdio>

const int kN = 100001;
int t, n, wei[kN], ans[kN];

int main() {
  for (int i = 2; i < kN; ++i) {
    ans[i] = ans[i - 1];
    if (++wei[1] > 0) ++ans[i];
    wei[i] -= 1;
    for (int j = 2; j * j <= i; ++j) {
      int k = i / j;
      if (j * k != i) continue;
      if (++wei[j] > 0) ++ans[i];
      wei[i] -= 1;
      if (j == k) continue;
      if (++wei[k] > 0) ++ans[i];
      wei[i] -= 1;
    }
  }

  scanf("%d", &t);
  while (t --> 0) {
    scanf("%d", &n);
    printf("%d\n", ans[n]);
  }
}
