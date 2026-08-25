#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vector a(N, vector<int>(M));
  for (auto &i : a) for (auto &j : i) cin >> j;

  int ans = 1;
  for (int u = 0; u < N; ++u) {
    vector<bool> can_u(M, true), can_l(M, true);
    can_l[0] = false;
    for (int d = u; d < N; ++d) {
      int len = 0;
      for (int i = 0; i < M; ++i) {
        if (d > u and a[d][i] <= a[d - 1][i]) can_u[i] = false;
        if (i > 0 and a[d][i] <= a[d][i - 1]) can_l[i] = false;
        if (not can_u[i] or not can_l[i]) len = 0;
        if (can_u[i]) ans = max(ans, (d - u + 1) * (++len));
      }
    }
  }

  cout << ans << '\n';

  return 0;
}
