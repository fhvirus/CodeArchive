#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,popcnt")
#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <bitset>
#include <numeric>

const int kN = 20;
const int kM = 100000001;

int64_t m;
int n, a[kN];
bool dp[kM];
int pos[1 << kN];

int main(){
	scanf("%ld%d", &m, &n);
	for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);
  std::sort(a, a + n);
  n = (int) (std::unique(a, a + n) - a);

	if (m < kM) {
    int ans = 0;
		for (int i = 0; i <= m; ++i) {
      ans += dp[i];
      if (dp[i]) continue;
			for (int j = 0; j < n; ++j) {
				if (i + a[j] > m) { n = j; break; }
				dp[i + a[j]] = 1;
			}
		}
		printf("%d\n", ans);
	} else {
    const int lim = a[n - 1];
    std::fill(pos, pos + (1 << lim), -1);

    int cur = (1 << lim) - 1;
    int mask = 0;
    for (int i = 0; i < n; ++i)
      mask |= 1 << (lim - a[i]);

    int st = -1, ed = -1;
    for (int i = 0; ; ++i) {
      dp[i] = (__builtin_popcount(cur & mask) < n);
      cur = (cur | (dp[i] << lim)) >> 1;
      if (pos[cur] != -1) {
        st = pos[cur], ed = i;
        break;
      }
      pos[cur] = i;
    }

    // for all i >= st, dp[i] = dp[st + (i - st) % (ed - st)]
    m += 1;
    int64_t cycle_num = std::max(0l, (m - st) / (ed - st));
    int64_t tail = std::max(0l, m - st - cycle_num * (ed - st));
    int64_t ans = std::accumulate(dp, dp + st + tail, 0l);
    ans += cycle_num * std::accumulate(dp + st, dp + ed, 0l);
    printf("%ld\n", ans);
  }
}
