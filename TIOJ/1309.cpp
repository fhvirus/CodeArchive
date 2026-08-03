#include <bits/stdc++.h>
using namespace std;

const int kC = 1000;
int64_t tmp[(kC + 1) * (kC + 1)];

void solve() {
  int a, b, c, d, p, q, r, w;
  cin >> a >> b >> c >> d >> p >> q >> r >> w;
  array<vector<int>, 4> pw;
  for (int i = 0; i <= kC; ++i) {
    pw[1].push_back(i);
    pw[2].push_back(i * i);
    pw[3].push_back(i * i * i);
  }
  int e = 0;
  for (int s : pw[p]) for (int t : pw[q])
    tmp[e++] = (int64_t) a * s + (int64_t) b * t;
  sort(tmp, tmp + e);

  int64_t ans = 0;
  for (int u : pw[r]) for (int v : pw[w]) {
    int64_t f = -((int64_t) c * u + (int64_t) d * v);
    auto lb = lower_bound(tmp, tmp + e, f);
    auto rb = upper_bound(lb, tmp + e, f);
    ans += (int64_t) (rb - lb);
  }

  cout << ans << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while (T --> 0) solve();

  return 0;
}
