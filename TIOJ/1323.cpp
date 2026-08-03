#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-7;
template <class T = double>
struct Simplex {
  int n, m;
  vector<int> l, d;
  vector<vector<T>> a;
  vector<T> b, c, sol;
  T v;
  static bool eq(T a, T b) { return fabs(a - b) <= eps;  }
  static bool lt(T a, T b) { return a + eps < b; }
  void pivot(int x, int y) {
    T k = 1 / a[x][y]; a[x][y] = 1;
    for (int j = 0; j < n; ++j) a[x][j] *= k;
    b[x] *= k;
    for (int i = 0; i < m; ++i) if (i != x and abs(a[i][y]) > eps) {
      T mul = a[i][y]; a[i][y] = 0;
      for (int j = 0; j < n; ++j) a[i][j] -= a[x][j] * mul;
      b[i] -= b[x] * mul;
    }
    swap(l[x], d[y]);
    if (abs(c[y]) <= eps) return;
    k = c[y]; c[y] = 0; v += k * b[x];
    for (int j = 0; j < n; ++j) if (abs(a[x][j]) > eps)
      c[j] -= k * a[x][j];
  }
  int solve() { // 0: found solution, 1: infeasible, 2: unbounded
    iota(begin(d), end(d), 0);
    iota(begin(l), end(l), n);
    while (true) { // Eliminating negative b[i]
      int x = (int) (ranges::min_element(b, lt) - begin(b));
      if (not lt(b[x], 0)) break;
      int y = (int) (ranges::min_element(a[x], lt) - begin(a[x]));
      if (not lt(a[x][y], 0)) return 1;
      pivot(x, y);
    }
    while (true) {
      int y = (int) (ranges::max_element(c, lt) - begin(c));
      if (not lt(0, c[y])) break;
      int x = -1;
      for (int i = 0; i < m; ++i)
        if (lt(0, a[i][y]) and (x == -1 or lt(b[i]/a[i][y], b[x]/a[x][y]))) x = i;
      if (x == -1) return 2;
      pivot(x, y);
    }
    for (int i = 0; i < m; ++i)
      if (l[i] < n) sol[l[i]] = b[i];
    return 0;
  }
  Simplex(const auto& _a, const auto& _b, const auto& _c) :
    a(_a), b(_b), c(_c) {
    n = (int)size(c), m = (int)size(b);
    l.assign(m, 0);
    d.assign(n, 0); sol.assign(n, 0);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int m, n;
  cin >> m >> n;

  vector<double> R(m);
  for (auto &i : R) cin >> i;

  vector a(m, vector<double>(n));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> a[j][i];

  vector<double> C(n);
  for (auto &i : C) cin >> i;

  Simplex simplex(a, R, C);
  if (simplex.solve() != 0) exit(-1);

  cout << setprecision(3) << fixed << simplex.v << '\n';

  return 0;
}
