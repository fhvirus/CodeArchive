#include<bits/stdc++.h>
using namespace std;

/* Geometry Template */
const double eps = 1e-9;
int sign(const double& a) { return fabs(a) < eps ? 0 : ((a > 0) - (a < 0)); }

struct Vec {
	double x, y;
	Vec(const double& _x = 0, const double& _y = 0): x(_x), y(_y) {}
	void read() { cin >> x >> y; }
	const double abs() const { return sqrt(x * x + y * y); }
	const double abs2() const { return x * x + y * y; }
};
ostream& operator << (ostream& O, const Vec& v) { return O << '(' << v.x << ", " << v.y << ')'; }
#define opab(x) operator x (const Vec& a, const Vec& b)
bool opab(<) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
Vec opab(-) { return Vec(a.x - b.x, a.y - b.y); }
double opab(*) { return a.x * b.x + a.y * b.y; }
double opab(^) { return a.x * b.y - a.y * b.x; }

#define abc(x) x(const Vec& a, const Vec& b, const Vec& c)
int abc(ori) { return sign((b - a) ^ (c - a)); }
int abc(dir) { return sign((b - a) * (c - a)); }
bool abc(col) { return ori(a, b, c) == 0; }
bool abc(onl) { return col(a, b, c) and dir(c, a, b) <= 0; }
bool intersect(const Vec& a, const Vec& b, const Vec& c, const Vec& d) {
	return onl(a, b, c) or onl(a, b, d) or onl(c, d, a) or onl(c, d, b) or
		(ori(a, b, c) != ori(a, b, d) and ori(c, d, a) != ori(c, d, b));
}
double abc(dis) {
	if (sign((a - b).abs2()) == 0) return (c - a).abs();
	if (dir(a, b, c) >= 0 and dir(b, a, c) >= 0)
		return fabs(((b - a) ^ (c - a)) / (b - a).abs());
	return min((a - c).abs(), (b - c).abs());
}

void make_hull(vector<Vec>& a) {
	sort(begin(a), end(a));
	vector<Vec> hull;
	for (const auto& i: a) {
		while (hull.size() > 1 and ori(end(hull)[-2], end(hull)[-1], i) <= 0)
			hull.pop_back();
		hull.push_back(i);
	}
	int siz = hull.size();
	reverse(begin(a), end(a));
	for (const auto& i: a) {
		while ((int) hull.size() > siz and ori(end(hull)[-2], end(hull)[-1], i) <= 0)
			hull.pop_back();
		hull.push_back(i);
	}
	a.swap(hull);
}

bool inside(const Vec& p, const vector<Vec>& h) {
	int n = h.size() - 1, cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (onl(h[i], h[i + 1], p)) return true;
		cnt += intersect(p, Vec(1e9, p.y + 1), h[i], h[i + 1]);
	}
	return (cnt & 1);
}
/* Geometry Template */

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << setprecision(3) << fixed;

	int m, n;

	while (cin >> m >> n and not (m == 0 and n == 0)) {
		vector<Vec> a(m), b(n);
		for (Vec& i: a) i.read();
		for (Vec& i: b) i.read();

		make_hull(a); m = a.size() - 1;
		make_hull(b); n = b.size() - 1;

		double dist = 1e9;

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (intersect(a[i], a[i + 1], b[j], b[j + 1])) {
					dist = 0;
					break;
				}
			}
		}
		for (int i = 0; i < m; ++i)
			if (inside(a[i], b)) {
				dist = 0;
				break;
			}
		for (int i = 0; i < n; ++i)
			if (inside(b[i], a)) {
				dist = 0;
				break;
			}

		if (sign(dist) > 0) {
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < n; ++j) {
					dist = min(dist, dis(a[i], a[i + 1], b[j]));
					dist = min(dist, dis(b[j], b[j + 1], a[i]));
				}
			}
		}

		if (sign(dist) <= 0) cout << "IMPOSSIBLE\n";
		else cout << dist << '\n';
	}

	return 0;
}
