#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const double tau = 2 * M_PI;

  int n, r;
  cin >> n >> r;

  vector<int> x, y;
  for (int i = 0; i < n; ++i) {
    int xi, yi;
    cin >> xi >> yi;
    bool has = false;
    for (int j = 0; j < (int)size(x); ++j)
      has |= (x[j] == xi and y[j] == yi);
    if (not has) x.push_back(xi), y.push_back(yi);
  }
  n = (int)size(x);

  const auto f = [&](int i, double a) { return r * (r * a + x[i] * sin(a) - y[i] * cos(a)); };

  double ans = 0;
  for (int i = 0; i < n; ++i) {
    vector<pair<double, int>> es;
    int cnt = 0;
    for (int j = 0; j < n; ++j) if (j != i) {
      int dx = x[j] - x[i], dy = y[j] - y[i];
      int d2 = dx * dx + dy * dy;
      if (d2 >= 4 * r * r) continue;

      double c2c = atan2(dy, dx), a = acos(sqrt(d2) / 2 / r);
      double lb = c2c - a, rb = c2c + a;
      while (lb < 0) lb += tau;
      while (rb < 0) rb += tau;
      while (rb >= tau) rb -= tau;
      es.emplace_back(lb, 1);
      es.emplace_back(rb, -1);
      if (rb < lb) cnt += 1;
    }

    ranges::sort(es);
    if (cnt == 0) ans -= f(i, 0);
    for (auto [a, d] : es) {
      if (cnt == 0) ans += f(i, a);
      cnt += d;
      if (cnt == 0) ans -= f(i, a);
    }
    if (cnt == 0) ans += f(i, tau);
  }

  cout << setprecision(2) << fixed << ans / 2 << '\n';

  return 0;
}
