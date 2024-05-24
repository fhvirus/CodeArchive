#include <cstdio>
#include <algorithm>
#include <utility>

const int kN = 500005;
int n, h[kN];
int span_r[kN], stk[kN];
std::pair<int, int> cand[kN];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", h + i);

  h[0] = h[n + 1] = 1e9;

  int t = 0;
  stk[t] = 0;
  for (int i = 1; i <= n + 1; ++i) {
    while (t >= 0 and h[stk[t]] < h[i])
      span_r[stk[t--]] = i;
    stk[++t] = i;
  }

  t = 0;
  stk[t] = n + 1;
  for (int i = n, j = 0; i >= 0; --i) {
    while (t >= 0 and h[stk[t]] <= h[i]) {
      cand[j++] = std::make_pair(span_r[stk[t]] - i - 1, h[stk[t]]);
      t -= 1;
    }
    stk[++t] = i;
  }

  std::sort(cand, cand + n);
  for (int i = n - 1; i > 0; --i)
    cand[i - 1].second = std::min(cand[i - 1].second, cand[i].second);

  int q, d;
  scanf("%d", &q);
  while (q --> 0) {
    scanf("%d", &d);
    auto it = lower_bound(cand, cand + n, std::make_pair(d, 0));
    printf("%d\n", it->second);
  }

  return 0;
}
