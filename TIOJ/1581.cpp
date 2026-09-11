#include <cstdio>
#include <cstdint>
#include <algorithm>
using namespace std;

auto get(auto board, auto p) { return board >> (2 * p) & 0b11; }

void dfs(uint32_t board, uint32_t slot, int& ans) {
  if (slot == 0) {
    if ((++ans) == 1) {
      for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) printf("%u", 1 + get(board, i * 4 + j));
        puts("");
      }
    }
    return;
  }
  uint32_t p = __lg(slot & -slot), has = 0;
  for (uint32_t k = p & 0b0011; k <= (p | 0b1100); k += 0b0100) if (~slot >> k & 1) has |= 1 << get(board, k);
  for (uint32_t k = p & 0b1100; k <= (p | 0b0011); k += 0b0001) if (~slot >> k & 1) has |= 1 << get(board, k);
  for (int i : {0, 4}) for (int j : {0, 1}) if (~slot >> (p^i^j) & 1) has |= 1 << get(board, p^i^j);
  for (uint32_t v : {0, 1, 2, 3}) if (~has >> v & 1) dfs(board | (v << (2 * p)), slot ^ (1u << p), ans);
}

int main() {
  uint32_t board = 0, slot = 0;
  for (int p = 0; p < 16; ++p) {
    int t; scanf("%d", &t);
    if (0 > t or t > 4) { puts("I can not solve!!"); exit(0); }
    if (t == 0) slot |= (1u << p);
    else board |= (uint32_t)(t - 1) << (2 * p);
  }

  int ans = 0;
  dfs(board, slot, ans);
  if (ans > 0) printf("\nWe have %d way(s) to solve it!!\n", ans);
  else puts("I can not solve!!");

  return 0;
}
