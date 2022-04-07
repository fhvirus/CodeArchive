#include <bits/stdc++.h>
using namespace std;

const int64_t eps = 1e-8;
int sign(int64_t a) { return fabs(a) < eps ? 0 : (a > 0) - (a < 0); }

struct Vec {
	int64_t x, y;
	Vec(int64_t x = 0, int64_t y = 0): x(x), y(y) {}
	void read() { cin >> x >> y; }
};
#define opab(x) operator x (const Vec& a, const Vec& b)
Vec opab(+) { return {a.x + b.x, a.y + b.y}; }
Vec opab(-) { return {a.x - b.x, a.y - b.y}; }
int64_t opab(*) { return a.x * b.x + a.y * b.y; }
int64_t opab(^) { return a.x * b.y - a.y * b.x; }
int64_t abs2(const Vec& a) { return a * a; }
int64_t abs(const Vec& a) { return sqrt(a * a); }

#define FUNC(n) n(const Vec& a, const Vec& b, const Vec& c)
int FUNC(ori) { return sign((b - a) ^ (c - a)); }
bool FUNC(colinear) { return ori(a, b, c) == 0; }
bool FUNC(online) { return colinear(a, b, c) and sign((a - c) * (b - c)) <= 0; }
bool intersect(Vec a, Vec b, Vec c, Vec d) {
	if (online(a, b, c) or online(a, b, d) or online(c, d, a) or online(c, d, b))
		return true;
	return ori(a, b, c) != ori(a, b, d) and ori(c, d, a) != ori(c, d, b);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	vector<Vec> v(n + 1);
	for (int i = 0; i < n; ++i)
		v[i].read();
	v[n] = v[0];

	int64_t ans = 0;
	for (int i = 0; i < n; ++i)
		ans += (v[i] ^ v[i + 1]);

	cout << (ans < 0 ? -ans : ans) << '\n';

	return 0;
}
