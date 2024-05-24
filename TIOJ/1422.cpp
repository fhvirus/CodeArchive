#include <cstdio>
#include <algorithm>

// nm <= 120 ==> n <= 10
// ans <= n (trivial)
// ans <= m - 2 if m >= 3 (put on two diagonals and leave out corners)

const int kN = 10, kM = 100;
int n, m, ans;

bool hor[kN], ver[kM], dia[kN + kM], ant[kN + kM];
void dfs(int i, int c) {
  if (c >= ans) return;
  if (i == n) {
    for (int x = 0; x < n; ++x)
      for (int y = 0; y < m; ++y)
        if (!hor[x] and !ver[y] and !dia[y - x + n - 1] and !ant[x + y])
          return;
    ans = c;
    return;
  }
  hor[i] = true;
  for (int j = 0; j < m; ++j) {
    if (ver[j] or dia[j - i + n - 1] or ant[i + j]) continue;
    ver[j] = dia[j - i + n - 1] = ant[i + j] = true;
    dfs(i + 1, c + 1);
    ver[j] = dia[j - i + n - 1] = ant[i + j] = false;
  }
  hor[i] = false;
  dfs(i + 1, c);
}

int main() {

  scanf("%d%d", &n, &m);
  if (n > m) std::swap(n, m);

  if ((n - 1) * (m + 3 * n) < n * m) printf("%d\n", n);
  else {
    ans = (m >= 3 ? std::min(n, m - 2) : n);
    dfs(0, 0);
    printf("%d\n", ans);
  }

  return 0;
}
