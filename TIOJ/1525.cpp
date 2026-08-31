#include "lib1525.h"

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
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	P perp() const { return P(-y, x); } // rotates +90 degrees
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

template <class P>
double cc_radius(const P& A, const P& B, const P& C) {
  return (B-A).dist()*(C-B).dist()*(A-C).dist()/
    abs((B-A).cross(C-A))/2;
}
template <class P>
P cc_center(const P& A, const P& B, const P& C) {
  P b = C-A, c = B-A;
  return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}

typedef Point<double> P;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  Initialize();

  P waste;
  Getwaste(&waste.x, &waste.y);

  const auto ask = [](P p) { return Query(p.x, p.y); };

  const array<P, 3> dir = {P(1, 0), P(-1, 0), P(0, 1)};
  array<P, 3> e;
  for (int i : {0, 1, 2}) {
    e[i] = waste;
    for (double l = pow(2, 31); l > 1e-3; l /= 2)
      if (ask(e[i] + dir[i] * l)) e[i] = e[i] + dir[i] * l;
  }

  auto cen = cc_center(e[0], e[1], e[2]);
  auto r = cc_radius(e[0], e[1], e[2]);
  Report(cen.x, cen.y, r);

  return 0;
}
