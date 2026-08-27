#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,popcnt")
#include <cstdio>
#include <cstdint>
#include <bitset>
#include <vector>
using namespace std;

int PermToInt(uint64_t v) {
  int use = 0, i = 0, r = 0;
  for (int j = 0; j < 9; ++j) {
    auto x = v >> (j * 4) & 0xf;
    r = r * ++i + __builtin_popcount(use & -(1<<x));
    use |= 1 << x;
  }
  return r;
}

const int kS = 10878;
bitset<362880> easy;
uint64_t buf[2][kS];

int main() {
  const int dir[5] = {0, 1, 0, -1, 0};
  vector<int> adj[9];
  for (int z = 0; z < 9; ++z) {
    int i = z / 3, j = z % 3;
    for (int d : {0, 1, 2, 3}) {
      int ni = i + dir[d], nj = j + dir[d + 1];
      if (0 <= min(ni, nj) and max(ni, nj) < 3)
        adj[z].push_back(ni * 3 + nj);
    }
  }

  uint64_t start = 0;
  for (uint64_t j = 0; j < 9; ++j)
    start |= ((j + 1) % 9) << (j * 4);

  auto cur = buf[0], nxt = buf[1];
  int ncur = 0, nnxt = 0;

  easy[PermToInt(start)] = 1; cur[ncur++] = start << 4 | 8;
  for (int dis = 1; dis <= 20; ++dis) {
    nnxt = 0;
    for (int i = 0; i < ncur; ++i) {
      uint64_t u = cur[i];
      int z = u & 0xf; u >>= 4;
      for (int nz : adj[z]) {
        uint64_t v = u >> (nz * 4) & 0xf;
        uint64_t nu = u ^ (v << (z * 4)) ^ (v << (nz * 4));
        int id = PermToInt(nu);
        if (not easy[id]) {
          easy[id] = 1;
          if (dis < 20) nxt[nnxt++] = nu << 4 | nz;
        }
      }
    }
    swap(cur, nxt), swap(ncur, nnxt);
  }

  int k; scanf("%d", &k);
  while (k --> 0) {
    uint64_t a = 0;
    for (int j = 0; j < 9; ++j) { uint64_t t; scanf("%lu", &t); a |= t << (j * 4); }
    puts(easy[PermToInt(a)] ? "Easy" : "Hard");
  }

  return 0;
}
