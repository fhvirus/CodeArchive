#include <cstdio>

void solve(int n, int u, int v, int &t) {
  if (n > 1) solve(n - 1, u, v, t);
  printf("#%d : move the dish from #%d to #2\n", ++t, u);
  if (n > 1) solve(n - 1, v, u, t);
  printf("#%d : move the dish from #2 to #%d\n", ++t, v);
  if (n > 1) solve(n - 1, u, v, t);
}

int main() {
  int n, t = 0;
  scanf("%d", &n);
  solve(n, 1, 3, t);
  return 0;
}
