#include <bits/stdc++.h>
using namespace std;

template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
  auto operator <=> (const P& p) const = default;
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
};

template <class P>
vector<P> convex_hull(vector<P> ps) {
  if (size(ps) <= 1) return ps;
  ranges::sort(ps);
	vector<P> h(size(ps) + 1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, ranges::reverse(ps))
		for (P p : ps) {
			while (t >= s + 2 and h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
  h.resize(t - (t == 2 and h[0] == h[1]));
	return h;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  typedef Point<int> P;

  int b, r;
  cin >> b >> r;

  vector<P> bs(b), rs(r);
  for (auto &[x, y] : bs) cin >> x >> y;
  for (auto &[x, y] : rs) cin >> x >> y;

  vector<P> r_ut, r_in;
  {
    auto bh = convex_hull(bs); int hs = (int)size(bh);
    for (P p : rs) {
      bool in = (p.cross(bh[hs-1], bh[0]) >= 0);
      for (int i = 1; i < hs and in; ++i)
        in &= (p.cross(bh[i-1], bh[i]) >= 0);
      (in ? r_in : r_ut).push_back(p);
    }
  }
  if (empty(r_in)) { cout << 111 * r << '\n'; exit(0); }
  r = (int)size(r_in);

  const int INF = INT_MAX / 2;
  vector dis(b, vector<int>(b, INF));
  for (int i = 0; i < b; ++i) for (int j = 0; j < b; ++j) if (i != j) {
    bool f = true;
    for (int k = 0; k < r and f; ++k)
      f &= (bs[i].cross(bs[j], r_in[k]) >= 0);
    if (f) dis[i][j] = 1;
  }

  for (int k = 0; k < b; ++k)
    for (int i = 0; i < b; ++i) if (dis[i][k] != INF)
      for (int j = 0; j < b; ++j) if (dis[k][j] != INF)
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

  int min_cyc = INF;
  for (int i = 0; i < b; ++i) min_cyc = min(min_cyc, dis[i][i]);

  cout << 20 * min_cyc + 111 * (int)size(r_ut) << '\n';

  return 0;
}
