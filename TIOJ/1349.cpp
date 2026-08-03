// Lagrange's Four-Square Theorem
#include <cstdio>

int solve(int n) {
  int sq = 0;
  for (int l = 1 << 11; l; l /= 2)
    if ((sq + l) * (sq + l) <= n) sq += l;
  if (sq * sq == n) return 1;

  int t = n;
  bool two = true;
  for (int i = 2; i <= sq and two; ++i) {
    int k = 0;
    for (; t % i == 0; t /= i) k += 1;
    if (i % 4 == 3 and k % 2 == 1) two = false;
  }
  if (two and t > sq and t % 4 == 3) two = false;
  if (two) return 2;

  while (n % 4 == 0) n /= 4;
  return (n % 8 == 7 ? 4 : 3);
}

int main() {
  for (int N; scanf("%d", &N), N != 0; )
    printf("%d\n", solve(N));

  return 0;
}
