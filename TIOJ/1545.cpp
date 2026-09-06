#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-12;

struct BinomialRow {
  deque<double> a;
  int l, r;
  BinomialRow() : a {1}, l(0), r(0) {}
  void next() {
    a.push_front(0);
    r += 1;
    double mx = 0;
    for (int i = 0; i < r - l; ++i)
      mx = max(mx, (a[i] = (a[i] + a[i + 1]) / 2));
    mx = max(mx, a.back() /= 2);

    while (a[0] <= mx * eps) a.pop_front(), l += 1;
    while (a.back() <= mx * eps) a.pop_back(), r -= 1;
  }
  double operator [](int i) { return (l > i or i > r) ? 0 : a[i - l]; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vector<double> g(N + 1);
  g[1] = 1;

  BinomialRow br, bm;
  for (int i = 1; i <= N; ++i) {
    if (i == M) bm = br;
    if (i >= 2) {
      for (int j = max(1, br.l); j <= min(i - 1, br.r); ++j)
        g[i] += br[j] * g[i - j];
      g[i] = g[i] / 2 / (1 - pow(2, -i));
    }
    br.next();
  }

  double ans = 0;
  for (int i = max(0, bm.l); i <= min(M - 1, bm.r); ++i)
    ans += bm[i] * g[N - i];

  cout << setprecision(9) << fixed << ans << '\n';

  return 0;
}
