#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

const int kN = 101;
const int kD = 202;
int n, T[kN][kN];
int dis[kN][kN];
std::vector<std::pair<int, int>> qs[kD];

void relax(int i, int j, int v) {
  if (i < 0 or i > n or j < 0 or j > i) return;
  v = std::max(v, T[i][j] + 1);
  if (dis[i][j] > v) {
    dis[i][j] = v;
    qs[v].emplace_back(i, j);
  }
}

int main() {
  while (scanf("%d", &n) != EOF) {
    for (int i = 0; i < n; ++i)
      for (int j = 0; j <= i; ++j)
        scanf("%d", T[i] + j);

    for (int i = 0; i < n; ++i)
      for (int j = 0; j <= i; ++j)
        dis[i][j] = kD;

    dis[0][0] = T[0][0];
    qs[dis[0][0]].emplace_back(0, 0);

    for (int d = T[0][0]; d <= 100 + n; ++d) {
      for (auto [i, j] : qs[d]) {
        if (dis[i][j] < d) continue;
        relax(i - 1, j, d + 1);
        relax(i - 1, j - 1, d + 1);
        relax(i + 1, j, d + 1);
        relax(i + 1, j + 1, d + 1);
      }
      qs[d].clear();
    }

    int ans = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j <= i; ++j)
        ans = std::max(ans, dis[i][j]);

    printf("%d\n", ans);
  }
  return 0;
}
