#include <bits/stdc++.h>
using namespace std;

template<class T>
struct Point3D {
  typedef Point3D P;
  T x, y, z; int id;
  explicit Point3D(T _x = 0, T _y = 0, T _z = 0) : x(_x), y(_y), z(_z), id(-1) {}
  auto operator <=> (const P& o) const = default;
  P operator+(P p) const { return P(x+p.x, y+p.y, z+p.z); }
  P operator-(P p) const { return P(x-p.x, y-p.y, z-p.z); }
  T dist2() const { return x*x + y*y + z*z; }
};

typedef double T;
typedef Point3D<T> P;

struct Answer {
  T d2; int a, b;
  auto operator < (const Answer& o) const { return d2 < o.d2; }
};

void solve2(auto& ps, Answer& ans) {
  ranges::sort(ps, [](P a, P b) { return a.y < b.y; });
	set<P> S;
	int j = 0;
	for (P p : ps) {
		P d {ceil(sqrt(ans.d2)), 0, 0};
		while (ps[j].y <= p.y - d.x) S.erase(ps[j++]);
		auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
		for (; lo != hi; ++lo) ans = min(ans, {(*lo - p).dist2(), p.id, lo->id});
		S.insert(p);
	}
}

void solve(const auto& p, int lb, int rb, Answer& ans) {
  if (rb - lb < 20) {
    for (int i = lb; i < rb; ++i)
      for (int j = i - 1; j >= lb and (p[i].x - p[j].x) * (p[i].x - p[j].x) < ans.d2; --j)
        ans = min(ans, {(p[i] - p[j]).dist2(), p[i].id, p[j].id});
    return;
  }

  int mid = (lb + rb) / 2;
  solve(p, lb, mid, ans);
  solve(p, mid, rb, ans);

  vector<P> mp;
  T d = sqrt(ans.d2);
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
  for (int i = 0; i < N; ++i) {
    auto &[x, y, z, id] = p[i];
    cin >> x >> y >> z; id = i;
  }

  Answer ans = {(p[0] - p[1]).dist2(), 0, 1};
  for (int i = 2; i < N; ++i)
    ans = min(ans, {(p[i] - p[i - 1]).dist2(), i - 1, i});
  ranges::sort(p);
  solve(p, 0, N, ans);

  if (ans.a > ans.b) swap(ans.a, ans.b);
  printf("WARNING: galaxy%d and galaxy%d in %.06lf Uu\n", ans.a + 1, ans.b + 1, sqrt(ans.d2));

  return 0;
}
