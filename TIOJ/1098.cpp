#include <cstdio>
#include <algorithm>

int main() {
  int a, b, c;
  while (scanf("%d%d%d", &a, &b, &c), a != 0 or b != 0 or c != 0) {
    int g = std::__gcd(a, b);
    if (c % g) {
      puts("No");
      continue;
    }
    int l = a * b / g, ma = l / a, mb = l / b;

    int ans = 8e7;
    for (int x = 0; a * x <= c; ++x) {
      int y = (c - a * x) / b;
      if (a * x + b * y == c)
        ans = std::min(ans, 2 * x + 2 * y);
    }

    for (int y = 1; y < mb; ++y) {
      int x = (c + b * y) / a;
      if (a * x - b * y == c)
        ans = std::min(ans, 2 * x + 2 * y - 1);
    }

    for (int x = 1; x < ma; ++x) {
      int y = (c + a * x) / b;
      if (b * y - a * x == c)
        ans = std::min(ans, 2 * y + 2 * x - 1);
    }

    printf("%d\n", ans);
  }

  return 0;
}
