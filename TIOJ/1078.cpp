#include <cstdio>

int main() {
  long C[60][60];
  C[0][0] = 1;
  for (int i = 1; i < 60; ++i) {
    for (int j = 0; j <= i; ++j) {
      C[i][j] = 0;
      if (j > 0) C[i][j] += C[i - 1][j - 1];
      if (j < i) C[i][j] += C[i - 1][j];
    }
  }
  auto nCk = [&](int n, int k) -> long {
    if (0 > k or k > n) return 0l;
    return C[n][k];
  };
  
  int T;
  scanf("%d", &T);
  while (T --> 0) {
    long M;
    scanf("%ld", &M);

    int len = 64 - __builtin_clzl(M);
    long ans = 0;
    for (int l = 1; l < len; ++l) // highbit = l-th
      for (int k = l / 2; k < l; ++k)
        ans += nCk(l - 1, k);
    for (int l = 0; l < len - 1; ++l) { // highbit = len-th, highest diff = l-th
      if ((M & (1l << l)) == 0) continue;
      int has = __builtin_popcountl(M >> (l + 1));
      for (int i = len / 2 + 1; i < len; ++i)
        ans += nCk(l, i - has);
    }
    ans += (__builtin_popcountl(M) >= len / 2 + 1);

    printf("%ld\n", ans);
  }
  return 0;
}
