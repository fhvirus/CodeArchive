#include <bits/stdc++.h>
using namespace std;

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
  auto operator <=> (const P& p) const = default;
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	P perp() const { return P(-y, x); }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << setprecision(3) << fixed;
  typedef Point<double> P;

  for (P a, b; cin >> a.x >> a.y >> b.x >> b.y; ) {
    P c = (a + b) / 2, d = (b - a).perp() * sqrt(3) / 2;
    P u = c + d, v = c - d;
    if (u > v) swap(u, v);
    cout << u.x << ' ' << u.y << ' '
      << v.x << ' ' << v.y << '\n';
  }

  return 0;
}
