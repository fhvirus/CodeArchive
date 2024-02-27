#include <cstdio>
#include <algorithm>

int main(){
  int N, M, buf[2][10000], *sc = buf[0], *dp = buf[1];

  while(scanf("%d%d", &N, &M), N != 0 or M != 0){
    std::fill(sc, sc + M, -N);
    sc[0] = 0;
    for (int i = 0, a; i < N; ++i){
      scanf("%d", &a);
      std::copy(sc, sc + M, dp);
      for (int j = 0; j < M; ++j) {
        int nj = (j * 10 + a) % M;
        dp[nj] = std::max(dp[nj], sc[j] + 1);
      }
      std::swap(sc, dp);
    }

    int ans = 0;
    for (int i = 0; i < M; ++i)
      if (std::__gcd(i, M) == 1)
        ans = std::max(ans, sc[i]);
    printf("%d\n", ans);
  }
  return 0;
}
