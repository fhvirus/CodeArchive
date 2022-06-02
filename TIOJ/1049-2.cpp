#include <bits/stdc++.h>
using namespace std;

struct Vec {
	double x, y;
	Vec(double x = 0, double y = 0): x(x), y(y) {}
};
#define opab(x) operator x (const Vec& a, const Vec& b)
Vec opab(-) { return Vec(a.x - b.x, a.y - b.y); }
double opab(^) { return a.x * b.y - a.y * b.x; }
typedef array<Vec, 2> Seg;
double interatio(const Seg& a, const Seg& b) {
	const Vec v = a[1] - a[0];
	const double d1 = v ^ (b[0] - a[0]);
	const double d2 = v ^ (b[1] - a[0]);
	return (d1 * d2 < 0) ? (d1 / (d1 - d2)) : 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, ans;
	
	vector<Seg> segs;
	vector<double> ip;

	while (cin >> n and n != 0) {
		segs.resize(n);
		for (auto& s: segs)
			for (auto& p: s)
				cin >> p.x >> p.y;

		ans = 1;

		for (int i = 0; i < n; ++i) {
			ip.clear();
			ip.push_back(0);
			for (int j = 0; j < i; ++j)
				ip.push_back(interatio(segs[j], segs[i]));
			sort(begin(ip), end(ip));
			ans += (unique(begin(ip), end(ip)) - begin(ip));
		}

		cout << ans << '\n';
	}

	return 0;
}
