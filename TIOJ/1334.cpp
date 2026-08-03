#include <bits/stdc++.h>
using namespace std;

int sq(int x) { return x * x; }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<int> X(N), Y(N), r(N);
  for (int i = 0; i < N; ++i)
    cin >> X[i] >> Y[i] >> r[i];

  double ans = 0;
  vector<pair<double, int>> es;
  es.reserve(N * 2 + 2);
  for (int i = 0; i < N; ++i) {
    int cnt = 0;
    es.clear();
    es.emplace_back(0, 0);
    es.emplace_back(2 * M_PI, 0);

    bool in_other = false;
    for (int j = 0; j < N; ++j) if (j != i) {
      int dx = X[j] - X[i], dy = Y[j] - Y[i], d2 = sq(dx) + sq(dy);
      if (d2 >= sq(r[i] + r[j])) continue;
      if (d2 <= sq(r[i] - r[j])) {
        if (tie(r[i], i) > tie(r[j], j)) continue;
        in_other = true; break;
      }
      double theta = acos((sq(r[i]) + d2 - sq(r[j])) / (2 * r[i] * sqrt(d2))),
             alpha = atan2(dy, dx);
      double lb = alpha - theta, rb = alpha + theta;
      if (lb < 0) lb += 2 * M_PI;
      if (rb < 0) rb += 2 * M_PI;
      if (rb >= 2 * M_PI) rb -= 2 * M_PI;
      es.emplace_back(lb, 1);
      es.emplace_back(rb, -1);
      if (lb >= rb) cnt += 1;
    }
    if (in_other) continue;

    ranges::sort(es);
    double tot = 0;
    for (int j = 0; j + 1 < (int)size(es); ++j) {
      cnt += es[j].second;
      if (cnt == 0)
        tot += es[j + 1].first - es[j].first;
    }
    ans += tot * r[i];
  }

  int b = 0;
  for (; ans >= 10; ans /= 10) b += 1;
  cout << setprecision(4) << fixed
    << ans << ' ' << b << '\n';

  return 0;
}
