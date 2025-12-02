#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<pair<int64_t, int>> dat(N);
  const auto upd = [&](int u, int p) {
    auto& [sum, mx] = dat[u];
    sum += p;
    mx = max(mx, p);
  };
  for (int u, v, p, i = 1; i < N; ++i) {
    cin >> u >> v >> p;
    upd(u, p);
    upd(v, p);
  }

  int64_t ans = 0;
  for (auto [sum, mx] : dat) {
    if (mx * 2 > sum) ans += mx * 2 - sum;
    else ans += sum % 2;
  }

  cout << ans / 2 << '\n';

  return 0;
}
