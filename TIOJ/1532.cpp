#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  typedef double T;
  const T eps = 1e-8;

  int n;
  cin >> n;

  vector<pair<T, T>> line, end_x;
  vector<pair<T, int>> on_border;
  for (int i = 0; i < n; ++i) {
    T m, b;
    cin >> m >> b;

    vector<pair<T, T>> ps;
    if (0 <= b and b < 10) ps.emplace_back(b, 0);
    if (m != 0) {
      T x = (10 - b) / m;
      if (0 <= x and x < 10) ps.emplace_back(10 + x, x);
    }
    if (T y = m * 10 + b; 10 >= y and y > 0)
      ps.emplace_back(20 + (10 - y), 10);
    if (m != 0) {
      T x = -b / m;
      if (10 >= x and x > 0) ps.emplace_back(30 + (10 - x), x);
    }
    if (size(ps) < 2) continue;

    bool has = false;
    for (auto [om, ob] : line)
      if (abs(m - om) <= eps and abs(b - ob) <= eps)
        has = true;
    if (has) continue;

    int id = (int)size(line);
    line.emplace_back(m, b);
    end_x.emplace_back(ps[0].second, ps[1].second);
    for (auto [v, _] : ps)
      on_border.emplace_back(v, id);
  }
  ranges::sort(on_border);

  bool black = true;
  T sum_black = 0;
  vector<bool> done(size(line), false);
  for (auto [_, i] : on_border) {
    black = not black;
    if (done[i]) continue;

    auto [m, b] = line[i];
    auto [sx, ex] = end_x[i];
    vector<T> xs = {sx, ex};
    for (auto [om, ob] : line) if (abs(m - om) > eps) {
      T x = (ob - b) / (m - om), y = m * x + b;
      if (0 <= x and x <= 10 and 0 <= y and y <= 10)
        xs.push_back(x);
    }
    ranges::sort(xs);
    xs.erase(ranges::unique(xs).begin(), end(xs));
    if (sx > ex) ranges::reverse(xs);

    bool f = black;
    for (int j = 1; j < (int)size(xs); ++j) {
      T xa = xs[j - 1], xb = xs[j];
      T ya = m * xa + b, yb = m * xb + b;
      T t = xa * yb - xb * ya;
      sum_black += t * (f ? 1 : -1);
      f = not f;
    }

    done[i] = true;
  }

  for (T lb : {10, 20}) {
    black = true;
    int i = 0;
    T pre = lb, rb = lb + 10;
    for (; i < (int)size(on_border); ++i, black = not black) {
      T v = on_border[i].first;
      if (v < lb) continue;
      if (v > rb) break;
      if (black) sum_black += 10 * (v - pre);
      pre = v;
    }
    if (black) sum_black += 10 * (rb - pre);
  }

  sum_black /= 2;
  T sum_white = 10 * 10 - sum_black;
  if (sum_white > sum_black)
    swap(sum_white, sum_black);

  cout << setprecision(2) << fixed << sum_black << ' ' << sum_white << '\n';

  return 0;
}
