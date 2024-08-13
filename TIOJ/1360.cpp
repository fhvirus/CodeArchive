#include "lib1360.h"

void solve(int u, int d, int l, int r) {
  int i = (u + d) / 2;

  int ans_j = l, ans_v = Hey_Man(i, l);
  for (int j = l + 1, v; j < r; ++j) {
    v = Hey_Man(i, j);
    if (v > ans_v) ans_v = v, ans_j = j;
  }

  if (u < i) solve(u, i, l, ans_j);
  Report(ans_v);
  if (i + 1 < d) solve(i + 1, d, ans_j + 1, r);
}

int main() {
  WarCraft();
  int N = Find_n();
  int M = Find_m();
  solve(0, N, 0, M);
  return 0;
}
