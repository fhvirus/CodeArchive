#include <cstdio>
#include <algorithm>
#include <utility>

const int kN = 202;
int n, h[kN];
int nl, nr, hl[kN], hr[kN];
int dis[kN][kN][2];
std::tuple<int, int, int> q[kN * kN * 2];

int main() {
  while (scanf("%d", &n) != EOF and n != 0) {
    for (int d, i = 1; i <= n + 1; ++i) {
      scanf("%d", &d);
      if (i <= n)
        scanf("%d", h + i);
    }
    h[0] = h[n + 1] = 0;
    nl = (int) (std::max_element(h, h + n + 2) - h);
    nr = (n + 1) - nl;
    for (int i = 0; i <= nl; ++i) hl[i] = h[i];
    for (int i = 0; i <= nr; ++i) hr[i] = h[n + 1 - i];

    for (int i = 0; i < nl; ++i)
      for (int j = 0; j < nr; ++j)
        dis[i][j][0] = dis[i][j][1] = 8e7;

    int qh = 0, qt = 0;
    auto push = [&](int i, int j, int d, int v) {
      if (0 > i or 0 > j or i >= nl or j >= nr or dis[i][j][d] < v) return;
      dis[i][j][d] = v;
      q[qt++] = std::make_tuple(i, j, d);
    };
    push(0, 0, 0, 0);

    while (qh < qt) {
      auto [i, j, d] = q[qh++];
      int v = dis[i][j][d];
      push(i, j, 1 - d, v + 1);
      if (d == 0) { // going up
        int lt = std::max(hl[i], hl[i + 1]);
        int rt = std::max(hr[j], hr[j + 1]);
        if (lt == rt) push(i + (i & 1 ? -1 : 1), j + (j & 1 ? -1 : 1), 1, v + 1);
        if (lt <= rt) push(i + (i & 1 ? -1 : 1), j, 1, v + 1);
        if (lt >= rt) push(i, j + (j & 1 ? -1 : 1), 1, v + 1);
      } else { // going down
        int lb = std::min(hl[i], hl[i + 1]);
        int rb = std::min(hr[j], hr[j + 1]);
        if (lb == rb) push(i - (i & 1 ? -1 : 1), j - (j & 1 ? -1 : 1), 0, v + 1);
        if (lb >= rb) push(i - (i & 1 ? -1 : 1), j, 0, v + 1);
        if (lb <= rb) push(i, j - (j & 1 ? -1 : 1), 0, v + 1);
      }
    }

    printf("%d\n", dis[nl - 1][nr - 1][0]);
  }
  return 0;
}
