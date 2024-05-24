#include <cstdio>
#include <algorithm>

const int kN = 500005;
int n, h[kN];
int span_l[kN], stk[kN], ans[kN];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", h + i);

  h[0] = h[n + 1] = 1e9;
  std::fill(ans + 1, ans + 1 + n, 1e9);

  int t = 0;
  stk[t] = 0;
  for (int i = 1; i <= n + 1; ++i) {
    while (h[stk[t]] < h[i]) {
      int len = i - span_l[stk[t]] - 1;
      ans[len] = std::min(ans[len], h[stk[t--]]);
    }
    span_l[i] = stk[t];
    stk[++t] = i;
  }

  for (int i = n - 1; i >= 1; --i)
    ans[i] = std::min(ans[i], ans[i + 1]);

  int q, d;
  scanf("%d", &q);
  while (q --> 0) {
    scanf("%d", &d);
    printf("%d\n", ans[d]);
  }

  return 0;
}
