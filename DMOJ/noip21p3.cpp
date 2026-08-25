#include <bits/stdc++.h>
using namespace std;

template <class T>
void chmin(T &a, T b) { if (a > b) a = b; }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  int a0;
  cin >> a0;

  vector<int> d(n - 1);
  for (int i = 0, last = a0, t; i + 1 < n; ++i) {
    cin >> t;
    d[i] = t - last;
    last = t;
  }
  ranges::sort(d);

  int max_sum = 0;
  for (int i = n - 1; i >= 1; --i)
    max_sum += i * (d[i - 1]);

  vector<uint32_t> dp(max_sum + 1, UINT_MAX);
  dp[0] = 0;
  for (int i = 0, sum = 0, cur_max = 0; i < n - 1; ++i) {
    if (d[i] == 0) continue;
    sum += d[i];
    for (int j = cur_max; j >= 0; --j) if (dp[j] < UINT_MAX) {
      chmin(dp[j + sum], dp[j] + sum * sum);
      chmin(dp[j + (i + 1) * d[i]], dp[j] + (uint32_t)(i + 1) * d[i] * d[i] + 2u * d[i] * j);
      dp[j] = UINT_MAX;
    }
    cur_max += max(sum, (i + 1) * d[i]);
  }

  uint32_t ans = UINT_MAX;
  for (int j = 0; j <= max_sum; ++j)
    if (dp[j] < UINT_MAX) chmin(ans, n * dp[j] - (uint32_t) j * j);
  cout << ans << '\n';

  return 0;
}
