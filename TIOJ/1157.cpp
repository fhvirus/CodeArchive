#include <bits/stdc++.h>
using namespace std;

struct Frac {
  int64_t p, q;
  Frac (int64_t a = 0, int64_t b = 1) {
    assert(b != 0);
    if (b < 0) a = -a, b = -b;
    int64_t g = gcd(abs(a) % b, b);
    p = a / g, q = b / g;
  }
  Frac operator + (const Frac& o) const { return Frac(p * o.q + o.p * q, q * o.q); }
  Frac operator - (const Frac& o) const { return Frac(p * o.q - o.p * q, q * o.q); }
  Frac operator * (const Frac& o) const { return Frac(p * o.p, q * o.q); }
  Frac operator / (const Frac& o) const { return Frac(p * o.q, q * o.p); }
  friend ostream& operator << (ostream& O, Frac f) {
    if (f.q == 1) return O << f.p;
    return O << f.p << '/' << f.q;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  
  vector<valarray<Frac>> a;
  for (int t; cin >> t; ) {
    a.emplace_back(n + 1);
    a.back()[0].p = t;
    for (int i = 1; i <= n; ++i)
      cin >> a.back()[i].p;
  }

  int m = int(size(a)), rank = 0;
  for (int c = 0; c < n; ++c) {
    for (int r = rank; r < m; ++r) {
      if (a[r][c].p == 0) continue;
      swap(a[r], a[rank]);
      a[rank] = a[rank] / a[rank][c];
      for (int j = rank + 1; j < m; ++j)
        a[j] = a[j] - a[rank] * a[j][c];
      rank += 1;
      break;
    }
  }

  if (rank < n) {
    for (int r = rank; r < m; ++r)
      if (a[r][n].p != 0) {
        cout << "0\n";
        exit(0);
      }
    cout << "N\n";
    exit(0);
  }

  for (int r = n - 1; r >= 0; --r) {
    for (int j = r - 1; j >= 0; --j)
      a[j] = a[j] - a[r] * a[j][r];
  }

  cout << "1\n";
  for (int i = 0; i < n; ++i)
    cout << 'x' << i + 1 << " = " << a[i][n] << '\n';

  return 0;
}
