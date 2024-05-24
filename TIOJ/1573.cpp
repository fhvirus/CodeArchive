#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <utility>
#include <queue>
#include <map>
#include <cassert>

struct SwapTable {
  static constexpr int di[4] = {1, -1, 0, 0};
  static constexpr int dj[4] = {0, 0, 1, -1};
  int to[16][4], sz[16];
  constexpr SwapTable() : to{}, sz{} {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        for (int d = 0; d < 4; ++d) {
          int ni = i + di[d], nj = j + dj[d];
          if (0 <= ni and ni < 4 and 0 <= nj and nj < 4)
            to[i * 4 + j][sz[i * 4 + j]++] = ni * 4 + nj;
        }
      }
    }
  }
} swap_table;

struct DistTable {
  int dis[16][16];
  constexpr DistTable() : dis{} {
    for (int i = 0; i < 16; ++i)
      for (int j = 0; j < 16; ++j)
        dis[i][j] = std::abs(i / 4 - j / 4) + std::abs(i % 4 - j % 4);
  }
  int calc(uint64_t a) const {
    int ans = 0;
    for (int i = 0; i < 16; ++i) // don't count the blank
      if ((a >> (4 * i) & 15) != 15)
        ans += dis[(a >> (4 * i) & 15)][i];
    return ans;
  }
} dist_table;

void print_perm(uint64_t a) {
  for (int i = 0; i < 16; ++i)
    printf("%2lu%c", ((a >> (4 * i)) & 15), " \n"[i % 4 == 3]);
  puts("");
}
uint64_t swap_num(uint64_t a, int i, int j) { // a[i] = 15 = 0b1111
  uint64_t b = ((a >> (4 * i)) ^ (a >> (4 * j))) & 15;
  return a ^ (b << (4 * i)) ^ (b << (4 * j));
}

int IDAStar(uint64_t u, int e, uint64_t p, int g, int h, int lim) {
  // printf("e = %d, g = %d, h = %d:\n", e, g, h);
  // print_perm(u);
  if (h == 0) return g;
  if (g + h > lim) return 1e9;

  const int *to = swap_table.to[e], sz = swap_table.sz[e];
  int r = 1e9;
  for (int i = 0; i < sz; ++i) {
    uint64_t v = swap_num(u, e, to[i]);
    if (v == p) continue;
    int nh = h - dist_table.dis[u >> (4 * to[i]) & 15][to[i]]
      + dist_table.dis[u >> (4 * to[i]) & 15][e];
    r = std::min(r, IDAStar(v, to[i], u, g + 1, nh, lim));
  }

  return r;
}

int main() {
  int a[16], e;
  for (int i = 0; i < 16; ++i) {
    scanf("%d", a + i);
    if (a[i] == 0) e = i;
    a[i] = (a[i] == 0 ? 15 : a[i] - 1);
  }

  uint64_t s = 0;
  for (uint64_t i = 0; i < 16; ++i)
    s |= (uint64_t) a[i] << (4 * i);

  int parity = ((e / 4) ^ (e % 4)) & 1;
  for (int i = 0; i < 16; ++i) {
    while (a[i] != i) {
      parity ^= 1;
      std::swap(a[i], a[a[i]]);
    }
  }

  if (parity) {
    puts("-1");
    return 0;
  }

  int h = dist_table.calc(s), ans = 1e9;
  for (int lim = h; lim <= 50; ++lim) {
    ans = IDAStar(s, e, s, 0, h, lim);
    if (ans <= 50) break;
  }
  printf("%d\n", ans);

  return 0;
}
