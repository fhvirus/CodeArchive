#include <cstdio>
#include <algorithm>

int main() {
  int A, B, C, D;
  scanf("%d%d%d%d", &A, &B, &C, &D);

  int best = 0, bx = 0, by = 0, bz = 0;
  for (int y = 0; y <= std::min(A, B); ++y) {
    int x = std::min(A - y, C), z = std::min(B - y, D);
    int v = 80 * x + 100 * y + 60 * z;
    if (best < v) best = v, bx = x, by = y, bz = z;
  }

  printf("%d %d %d\n%d\n", bx, by, bz, best);

  return 0;
}
