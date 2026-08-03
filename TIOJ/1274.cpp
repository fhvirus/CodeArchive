#include <cstdio>

const int ans[3] = {
  2 /* Deemo */ + 1 /* Charlotte */,
  2 /* 遊戲人生 */ + 2 /* 我的英雄學院 */,
  /* 中二病也想談戀愛 => y = 2 */
  /* 東京闇鴉 => Tokyo, x = 5 */
  /* 雙星之陰陽師 => 辛 = 2 */
  2 * (5 + 2)
};

int main() {
  int n;
  scanf("%d", &n);
  printf("%d\n", ans[n - 1]);
  return 0;
}

