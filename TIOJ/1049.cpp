#include<bits/stdc++.h>
using namespace std;
#define pb emplace_back

const double eps = 1e-8;
int sign(double a) { return fabs(a) < eps ? 0 : (a > 0) - (a < 0); }

struct Vec {
	double x, y;
	Vec(double xx = 0, double yy = 0): x(xx), y(yy) {}
};
istream& operator >> (istream& I, Vec v)
{ return I >> v.x >> v.y; }
ostream& operator << (ostream& O, Vec v)
{ return O << '(' << v.x << ',' << v.y << ')'; }
Vec operator * (Vec a, double b) { return Vec(a.x * b, a.y * b); }
Vec operator / (Vec a, double b) { return Vec(a.x / b, a.y / b); }
#define opab(x) operator x (Vec a, Vec b)
bool opab(<) { return a.x == b.x ? a.y < b.y : a.x < b.x; }
bool opab(==) { return sign(a.x - b.x) == 0 and sign(a.y - b.y) == 0; }
Vec opab(+) { return Vec(a.x + b.x, a.y + b.y); }
Vec opab(-) { return Vec(a.x - b.x, a.y - b.y); }
double opab(*) { return a.x * b.x + a.y * b.y; }
double opab(^) { return a.x * b.y - a.y * b.x; }
#define abc(x) x(Vec a, Vec b, Vec c)
int abc(ori) { return sign((b - a) ^ (c - a)); }
int abc(dir) { return sign((b - a) * (c - a)); }
bool abc(col) { return ori(a, b, c) == 0; }
bool abc(onl) { return col(a, b, c) and dir(c, a, b) <= 0; }
bool intersect(Vec a, Vec b, Vec c, Vec d) {
	return onl(a, b, c) or onl(a, b, d) or onl(c, d, a) or onl(c, d, b)
		or (ori(a, b, c) != ori(a, b, d) and ori(c, d, a) != ori(c, d, b));
}
Vec interpoint(Vec a, Vec b, Vec c, Vec d) {
	double p1 = (b - a) ^ (c - a), p2 = (d - a) ^ (b - a);
	return a + ((c - a) * p2 + (d - a) * p1) / (p1 + p2);
}

typedef pair<Vec, Vec> Seg;
const Vec corner[4] = { Vec(0, 0), Vec(0, 1), Vec(1, 1), Vec(1, 0) };
bool intersect(Seg a, Seg b)
{ return intersect(a.first, a.second, b.first, b.second); }
Vec interpoint(Seg a, Seg b)
{ return interpoint(a.first, a.second, b.first, b.second); }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	double a, b, c, d;
	vector<Seg> segs;
	vector<Vec> pts;

	while (cin >> n and n != 0) {
		segs.clear();
		segs.reserve(n);
		for (int i = 0; i < 4; ++i)
			segs.pb(corner[i], corner[(i + 1) & 3]);
		for (int i = 0; i < n; ++i) {
			cin >> a >> b >> c >> d;
			segs.pb(Vec(a, b), Vec(c, d));
		}
		n += 4;

		pts.clear();
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (intersect(segs[i], segs[j]))
					pts.push_back(interpoint(segs[i], segs[j]));
			}
		}

		sort(begin(pts), end(pts));
		pts.erase(unique(begin(pts), end(pts)), end(pts));


		int E = 0;
		int V = pts.size();

		for (int i = 0; i < n; ++i) {
			int cnt = 0;
			for (const Vec& p: pts) {
				if (onl(segs[i].first, segs[i].second, p))
					++cnt;
			}
			E += cnt - 1;
		}

		cout << E + 1 - V << '\n';
	}
	return 0;
}
