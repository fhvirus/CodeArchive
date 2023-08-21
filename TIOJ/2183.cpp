#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int sign(ll a) { return (a > 0) - (a < 0); }

struct Vec {
	ll x, y;
	Vec (ll x = 0, ll y = 0): x(x), y(y) {}
};
ostream& operator << (ostream& O, const Vec& v)
{ return O << '(' << v.x << ',' << v.y << ')'; }
#define opab(x) operator x (const Vec& a, const Vec& b)
bool opab(<) { return a.x < b.x; }
Vec opab(-) { return Vec(a.x - b.x, a.y - b.y); }
ll opab(^) { return a.x * b.y - a.y * b.x; }
int ori(const Vec& a, const Vec& b, const Vec& c)
{ return sign((b - a) ^ (c - a)); }

typedef pair<Vec, Vec> Seg;
bool operator < (const Seg& a, const Seg& b)
{ return ((a.second - a.first) ^ (b.second - b.first)) > 0; }
bool operator > (const Seg& a, const Seg& b)
{ return ((a.second - a.first) ^ (b.second - b.first)) < 0; }

void make_hull(vector<Vec>& a) {
	vector<Vec> hull(1, a[0]);
	for (int d = 0; d < 2; ++d, reverse(begin(a), end(a)))
		for (int s = hull.size(), i = 1; i < a.size(); hull.push_back(a[i++]))
			while (hull.size() > s and ori(end(hull)[-2], end(hull)[-1], a[i]) <= 0)
				hull.pop_back();
	a.swap(hull);
	a.pop_back();
}

pair<double, double> interpoint(const Seg& a, const Seg& b) {
	Vec v = a.second - a.first;
	double a1 = v ^ (b.first - a.first);
	double a2 = (b.second - a.first) ^ v;
	double x = (a2 * b.first.x + a1 * b.second.x) / (a1 + a2);
	double y = (a2 * b.first.y + a1 * b.second.y) / (a1 + a2);
	return pair<double, double>(x, y);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	vector<Vec> p(n);
	for (auto& i: p) cin >> i.x >> i.y;
	sort(begin(p), end(p));

	vector<Vec> a(begin(p), begin(p) + n / 2);
	vector<Vec> b(begin(p) + n / 2, end(p));

	make_hull(a); int sa = a.size();
	make_hull(b); int sb = b.size();
	rotate(begin(b), max_element(begin(b), end(b)), end(b));
	a.push_back(a[0]);
	b.push_back(b[0]);

	Seg mx(a[0], b[0]);
	for (int i = 0, j = 0; i < sa; ++i) {
		while (j < sb and ori(a[i], b[j], b[j + 1]) >= 0) ++j;
		mx = max(mx, Seg(a[i], b[j]));
	}

	reverse(begin(a), end(a));
	reverse(begin(b), end(b));

	Seg mn(a[0], b[0]);
	for (int i = 0, j = 0; i < sa; ++i) {
		while (j < sb and ori(a[i], b[j], b[j + 1]) <= 0) ++j;
		mn = min(mn, Seg(a[i], b[j]));
	}

	auto ip = interpoint(mx, mn);
	cout << setprecision(2) << fixed;
	cout << ip.first << ' ' << ip.second << '\n';

	return 0;
}
