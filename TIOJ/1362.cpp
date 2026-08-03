#include <cstdio>
#include <algorithm>
using namespace std;

int N, t[15], dp[1 << 15];

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i)
    scanf("%d", t + i);

  for (int i = 1; i < (1 << N); ++i)
    dp[i] = dp[i ^ (i & -i)] + t[__lg(i & -i)];

  for (int i = 1; i < (1 << N); ++i) {
    if ((i & (i - 1)) == 0) { dp[i] = 1; continue; }

    int v = dp[(1 << N) - 1] * N;
    for (int j = ((i - 1) & i); j; j = ((j - 1) & i))
      v = min(v, max(dp[j], dp[i ^ j]));
    dp[i] += v;
  }

  printf("%d\n", dp[(1 << N) - 1]);

  return 0;
}
