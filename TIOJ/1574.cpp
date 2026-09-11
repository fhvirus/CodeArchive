#include <bits/stdc++.h>
using namespace std;

struct Vert { int x, d, u; };

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n; cin >> n;
  vector<Vert> v(n);
  for (auto &[x, d, u] : v) cin >> x >> d >> u;

  int m; cin >> m;
  int64_t ans = 0;
  for (int y, l, r, vl = 0, vr = 0, pr = -1, i = 0; i < m; ++i) {
    cin >> y >> l >> r;
    while (vl < n and (v[vl].x < l or v[vl].d > y)) ++vl;
    while (vr + 1 < n and v[vr + 1].x <= r and v[vr + 1].u >= y) ++vr;
    ans += max(0, pr - vl);
    pr = vr;
  }

  cout << ans << '\n';

  return 0;
}
