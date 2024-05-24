#pragma GCC optimize("Ofast")
#include <cstdio>
#include <algorithm>

int a[5][5], ans = 0;

const int di[4] = {1, -1, 0, 0};
const int dj[4] = {0, 0, 1, -1};

inline int val(int i, int j) { return (0 <= i and i < 5 and 0 <= j and j < 5 ? a[i][j] : 0); }
bool check(int i, int j) {
  int m = 0, t = ((1 << a[i][j]) - 1) >> 1;
  for (int d = 0; d < 4; ++d)
    m |= 1 << val(i + di[d], j + dj[d]);
  return ((m >> 1) & t) == t;
}

void dfs(int i, int j, int cur) {
  if (i == 5) {
    for (int k = 0; k < 5; ++k)
      if (!check(4, k)) return;
    ans = std::max(ans, cur);
    return;
  }
  // Let the following lines be 4 3 4 3 4
  // so current line must only be 1 2
  if ((4 - i) * 18 + (4 - j) * 2 + cur <= ans) return;
  for (int v = 1; v <= 4; ++v) {
    a[i][j] = v;
    if (i == 0 or check(i - 1, j))
      dfs(i + (j == 4), j == 4 ? 0 : j + 1, cur + v);
  }
}

int main() {

  dfs(0, 0, 0);

  printf("%d\n", ans);

  return 0;
}
