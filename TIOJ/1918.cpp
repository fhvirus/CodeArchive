#include <bits/stdc++.h>
using namespace std;

template<class T>
struct Point3D {
  typedef Point3D P;
  T x, y, z;
  explicit Point3D(T _x = 0, T _y = 0, T _z = 0) : x(_x), y(_y), z(_z) {}
  auto operator <=> (const P& o) const = default;
  P operator+(P p) const { return P(x+p.x, y+p.y, z+p.z); }
  P operator-(P p) const { return P(x-p.x, y-p.y, z-p.z); }
  uint64_t dist2() const { return (uint64_t) x*x + y*y + z*z; }
};

typedef double T;
typedef Point3D<int64_t> P;

void solve2(auto& ps, uint64_t& ans) {
  ranges::sort(ps, [](P a, P b) { return a.y < b.y; });
	set<P> S;
	int j = 0;
	for (P p : ps) {
		P d {(int64_t) ceil(sqrt(ans)), 0, 0};
		while (ps[j].y <= p.y - d.x) S.erase(ps[j++]);
		auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
		for (; lo != hi; ++lo) ans = min(ans, (*lo - p).dist2());
		S.insert(p);
	}
}

void solve(const auto& p, int lb, int rb, uint64_t& ans) {
  if (rb - lb < 20) {
    for (int i = lb; i < rb; ++i)
      for (int j = i - 1; j >= lb and (p[i].x - p[j].x) * (p[i].x - p[j].x) < ans; --j)
        ans = min(ans, (p[i] - p[j]).dist2());
    return;
  }

  int mid = (lb + rb) / 2;
  solve(p, lb, mid, ans);
  solve(p, mid, rb, ans);

  vector<P> mp;
  int64_t d = (int64_t) ceil(sqrt(ans));
  for (int i = lb; i < rb; ++i)
    if (abs(p[i].x - p[mid].x) <= d)
      mp.push_back(p[i]);
  solve2(mp, ans);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<P> p(N);
  for (auto &[x, y, z] : p) cin >> x >> y >> z;
  ranges::sort(p);

  uint64_t ans = (p[0] - p[1]).dist2();
  solve(p, 0, N, ans);

  cout << ans << '\n';

  return 0;
}
