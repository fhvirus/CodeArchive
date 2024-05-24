#include <cstdio>
#include <algorithm>

// abcorz
// Binary search for the answer x.
// For some consecutive a's (space between holes, circular),
// if their sum is > x, then there must be >= 2 stones between them.
// No need to consider segments covering both of the first two holes,
// since there are always 2 >= 2 stones.

const int kN = 30003;
int N, M, a[kN], pre[kN];

// \forall 1 <= j < i <= N, pre[i] - pre[j - 2] > x
//  => pre_stone[i] - pre_stone[j - 1] >= 2
int pre_stone[kN];
bool check(int x) {
  std::fill(pre_stone, pre_stone + N + 1, 0);
  pre_stone[1] = 1;
  for (int j = 1, i = 1; j <= N; ++j) {
    i = std::max(i, j + 1);
    while (i <= N and pre[i] - (j >= 2 ? pre[j - 2] : 0) <= x) i += 1;
    // put at least two stones in different spots
    pre_stone[i - 1] = std::max(pre_stone[i - 1], pre_stone[j - 1] + 1);
    pre_stone[i] = std::max(pre_stone[i], pre_stone[j - 1] + 2);
    pre_stone[j + 1] = std::max(pre_stone[j + 1], pre_stone[j]);
  }
  pre_stone[N] = std::max(pre_stone[N - 1] + 1, pre_stone[N]);
  return pre_stone[N] <= M;
}

int main() {

  while (scanf("%d%d", &N, &M) != EOF) {
    for (int i = 0; i < N; ++i)
      scanf("%d", &a[i]);
    a[N] = a[0];
    for (int i = 0; i <= N; ++i)
      pre[i] = a[i] + (i >= 1 ? pre[i - 1] : 0);
    pre[N + 1] = pre[N];

    int ans = pre[N - 1], bound = 0;
    for (int i = 0; i < N; ++i)
      bound = std::max(bound, a[i] + a[i + 1]);
    for (int l = (1 << 30); l > 0; l >>= 1)
      if (ans - l >= bound and check(ans - l))
        ans -= l;

    printf("%d\n", ans);
  }

  return 0;
}
