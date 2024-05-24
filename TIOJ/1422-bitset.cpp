#include <cstdio>
#include <algorithm>
#include <bitset>

const int kM = 120;
int n, m, ans;
std::bitset<kM> mask[kM], tar;

void dfs(int i, int cnt, std::bitset<kM> cur) {
  if (cnt >= ans) return;
  if (cur.none()) {
    ans = cnt;
    return;
  }
  if (i >= n * m) return;
  dfs(cur._Find_next(i), cnt, cur);
  cur &= mask[i];
  dfs(cur._Find_next(i), cnt + 1, cur);
}

int main() {
  scanf("%d%d", &n, &m);
  if (n > m) std::swap(n, m);

  if ((n - 1) * (m + 3 * n) < n * m) printf("%d\n", n);
  else {
    ans = (m >= 3 ? std::min(n, m - 2) : n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        mask[i * m + j].set();
        for (int ni = 0; ni < n; ++ni) mask[i * m + j].reset(ni * m + j);
        for (int nj = 0; nj < m; ++nj) mask[i * m + j].reset(i * m + nj);
        for (int d = -n; d <= n; ++d)
          if (0 <= i + d and i + d < n and 0 <= j + d and j + d < m)
            mask[i * m + j].reset((i + d) * m + (j + d));
        for (int d = -n; d <= n; ++d)
          if (0 <= i - d and i - d < n and 0 <= j + d and j + d < m)
            mask[i * m + j].reset((i - d) * m + (j + d));
      }
    }
    std::bitset<kM> cur;
    for (int i = 0; i < n * m; ++i) cur.set(i);
    dfs(0, 0, cur);
    printf("%d\n", ans);
  }

  return 0;
}
