// Ref: https://oeis.org/A062714
#include <cstdio>

int main() {
  int X;
  scanf("%d", &X);
  puts("a");
  puts("aba");
  for (int i = 3; i <= X; ++i) {
    for (int j = 0; j < i; ++j)
      putchar('a' + j);
    for (int j = 0; j < (i - 3) * (i - 1) + 2; ++j) {
      if (j % (i - 2) == 0) putchar('a');
      putchar('b' + j % (i - 1));
    }
    putchar('\n');
  }
}
