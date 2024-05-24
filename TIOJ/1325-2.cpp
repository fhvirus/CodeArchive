#include <cstdio>

const int kN = 100001;
int t, n, cnt[kN], ans[kN];

int main() {
  for (int i = 1; i < kN; ++i) {
    for (int j = i + i; j < kN; j += i) ++cnt[j];
    for (int j = i * (cnt[i] + 2); j < kN; j += i) ++ans[j];
  }
  for (int i = 1; i < kN; ++i) ans[i] += ans[i - 1];

  scanf("%d", &t);
  while (t --> 0) {
    scanf("%d", &n);
    printf("%d\n", ans[n]);
  }
}
