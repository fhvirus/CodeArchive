#include <bits/stdc++.h>
using namespace std;

struct Vec {
	int64_t x, y;
	Vec(int64_t x = 0, int64_t y = 0): x(x), y(y) {}
	void read() { cin >> x >> y; }
};
#define opab(x) operator x (const Vec& a, const Vec& b)
Vec opab(-) { return {a.x - b.x, a.y - b.y}; }
int64_t opab(^) { return a.x * b.y - a.y * b.x; }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	vector<Vec> polygon(n);
	for (Vec& i: polygon) i.read();
	polygon.push_back(polygon[0]);
	
	int64_t area = 0, on = 0;
	for (int i = 0; i < n; ++i) {
		area += polygon[i] ^ polygon[i + 1];
		Vec p = polygon[i] - polygon[i + 1];
		on += gcd(p.x, p.y);
	}

	if (area < 0) area = -area;

	// A = i + b / 2 - 1
	// 2 * A = 2 * i + b - 2
	// i = (2 * A + 2 - b) / 2
	int64_t in = (area + 2 - on) / 2;

	cout << in << ' ' << on << '\n';

	return 0;
}
