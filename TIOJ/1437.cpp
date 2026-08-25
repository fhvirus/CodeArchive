#include <cstdio>

int main() {
  int w;
  scanf("%d", &w);

  int p_max = -1;
  for (int i = 0; i < w; ++i) {
    int c_max = -1;
    for (int n, j = 0; j < w; ++j) {
      scanf("%d", &n);
      if (n > p_max) printf("(%d,%d)\n", j, i);
      if (c_max < n) c_max = n;
    }
    p_max = c_max;
  }

  return 0;
}
