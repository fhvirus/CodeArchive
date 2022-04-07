#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
int sign(double a) { return fabs(a) < eps ? 0 : (a > 0) - (a < 0); }

struct Vec {
	double x, y;
	Vec(double x = 0, double y = 0): x(x), y(y) {}
	void read() { cin >> x >> y; }
};
#define opab(x) operator x (const Vec& a, const Vec& b)
Vec opab(+) { return { a.x + b.x, a.y + b.y }; }
Vec opab(-) { return { a.x - b.x, a.y - b.y }; }
double opab(*) { return a.x * b.x + a.y * b.y; }
double opab(^) { return a.x * b.y - a.y * b.x; }
double abs2(const Vec& a) { return a * a; }
double abs(const Vec& a) { return sqrt(a * a); }

#define TRI(n) n(const Vec& a, const Vec& b, const Vec& c)
int TRI(ori) { return sign((b - a) ^ (c - a)); }
bool TRI(colinear) { return ori(a, b, c) == 0; }
bool TRI(online) { return ori(a, b, c) == 0 and (a - c) * (b - c) <= 0; }
bool intersect(const Vec& a, const Vec& b, const Vec& c, const Vec& d) {
	return (online(a, b, c) or online(a, b, d) or online(c, d, a) or online(c, d, b))
		or (ori(a, b, c) != ori(a, b, d) and ori(c, d, a) != ori(c, d, b));
}

const Vec far(0, 1e9 + 7);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<Vec> polygon(n);
	for (Vec& i: polygon)
		i.read();
	polygon.push_back(polygon[0]);

	while (m --> 0) {
		Vec p;
		p.read();

		int cnt = 0;
		bool on = false;

		for (int i = 0; i < n and !on; ++i) {
			if (online(polygon[i], polygon[i + 1], p))
				on = true;
			if (intersect(polygon[i], polygon[i + 1], p, far))
				cnt += 1;
		}

		if (on) {
			cout << "BOUNDARY\n";
		} else if (cnt & 1) {
			cout << "INSIDE\n";
		} else {
			cout << "OUTSIDE\n";
		}
	}

	return 0;
}
