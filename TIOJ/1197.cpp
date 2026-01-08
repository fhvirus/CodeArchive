#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int M, N;
  cin >> M >> N;

  vector<int> g(M);
  for (int u, v; cin >> u >> v; ) {
    u -= 1; v -= 1;
    g[u] |= (1 << v);
    g[v] |= (1 << u);
  }

  vector<bool> can(1 << M);
  can[0] = true;
  for (int i = 1; i < (1 << M); ++i) {
    int u = __lg(i & -i);
    can[i] = can[i ^ (1 << u)] and (g[u] & i) == 0;
  }

  int64_t ans = 0, mxc = 0;
  vector<int64_t> dp(1 << M);
  dp[0] = 1;
  for (int t = 1; t <= max(N, M); ++t) {
    for (int i = (1 << M) - 1; i > 0; --i) {
      for (int j = i; j; j = (j - 1) & i) if (can[j])
        dp[i] += dp[i ^ j];
    }
    if (dp.back() and mxc == 0) mxc = t;
    if (t == N) ans = dp.back();
  }
  cout << ans << '\n' << mxc << '\n';

  return 0;
}
