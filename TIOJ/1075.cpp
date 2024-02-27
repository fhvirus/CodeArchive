#include <cstdio>
#include <cstring>
#include <algorithm>

const int kN = 10;

const char item_name[10][12] = {
  "RedWater", "OrangeWater", "BlueWater", "WhiteWater",
  "Arrow", "Bolt", "BrozenArrow", "BrozenBolt", "IronArrow", "IronBolt"
};
int item_count[10], item_num[10][kN];

// Observation: There exists an optimal solution where no item is split into > 2 slots.
//              Just split another item instead.
int dp[1 << kN][2];
int solve(int lim, int cnt, int num[kN]) {
  if (cnt == 0) return 0;
  for (int i = 0; i < (1 << cnt); ++i)
    dp[i][0] = cnt, dp[i][1] = 0;

  dp[0][0] = 0;
  for (int i = 1; i < (1 << cnt); ++i) {
    dp[i][1] = dp[i ^ (i & -i)][1] + num[std::__lg(i & -i)];
    if (dp[i][1] >= lim) dp[i][1] -= lim;
    for (int j = 0; j < cnt; ++j) if (i >> j & 1)
      dp[i][0] = std::min(dp[i][0], dp[i ^ (1 << j)][0] + (dp[i ^ (1 << j)][1] != 0));
  }
  return dp[(1 << cnt) - 1][0];
}

int main() {
  int T;
  scanf("%d", &T);
  while (T --> 0) {
    std::fill(item_count, item_count + 10, 0);

    int N;
    scanf("%d", &N);

    char name[12];
    int num;
    for (int i = 0; i < N; ++i) {
      scanf("%s%d", name, &num);
      for (int j = 0; j < 10; ++j) {
        if (strcmp(name, item_name[j]) != 0) continue;
        if (num == (j < 4 ? 100 : 1000)) continue;
        item_num[j][item_count[j]++] = num;
        break;
      }
    }

    int ans = 0;
    for (int j = 0; j < 10; ++j)
      ans += solve(j < 4 ? 100 : 1000, item_count[j], item_num[j]);

    printf("%d\n", ans);
  }
  return 0;
}
