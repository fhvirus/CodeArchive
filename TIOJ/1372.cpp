#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n, m; cin >> n >> m; ) {
    vector<int64_t> e(m);
    vector<bool> has(n, false);
    for (int u, v, i = 0; i < m; ++i) {
      cin >> u >> v;
      e[i] = (1l << u) | (1l << v);
      has[u] = has[v] = true;
    }
    if (ranges::find(has, false) != end(has)) {
      cout << -1 << '\n';
      continue;
    }
    int ans = m;
    for (int i = 1; i < (1 << m); ++i) {
      int p = popcount((unsigned)i);
      if (p >= ans or (n + 1) / 2 > p) continue;
      int64_t had = 0;
      for (int t = i; t; t -= t & -t) had |= e[__lg(t & -t)];
      if (had == (1l << n) - 1) ans = min(ans, p);
    }
    cout << ans << '\n';
  }

  return 0;
}
