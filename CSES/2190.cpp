#include <bits/stdc++.h>
using namespace std;

const int64_t eps = 1e-12;
struct Vec {
	int64_t x, y;
	Vec(int64_t x = 0, int64_t y = 0): x(x), y(y) {}
	void read() { cin >> x >> y; }
};

#define opab(x) operator x (Vec a, Vec b)
Vec opab(+) { return Vec(a.x + b.x, a.y + b.y); }
Vec opab(-) { return Vec(a.x - b.x, a.y - b.y); }
int64_t opab(*) { return (a.x * b.x + a.y * b.y); }
int64_t opab(^) { return (a.x * b.y - a.y * b.x); }
int64_t abs2(Vec a) { return a * a; }
int64_t abs(Vec a) { return sqrt(a * a); }

int sign(int64_t a) { return fabs(a) < eps ? 0 : (a > 0) - (a < 0); }
int ori(Vec o, Vec a, Vec b) { return sign((a - o) ^ (b - o)); }
bool colinear(Vec a, Vec b, Vec c) { return ori(c, a, b) == 0; }
bool online(Vec a, Vec b, Vec c) { return colinear(a, b, c) and sign((a - c) * (b - c)) <= 0; }
bool intersect(Vec a, Vec b, Vec c, Vec d) {
	return (online(a, b, c) or online(a, b, d) or online(c, d, a) or online(c, d, b)) or
		(ori(a, b, c) != ori(a, b, d) and ori(c, d, a) != ori(c, d, b));
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int t;
	cin >> t;

	Vec a, b, c, d;
	while (t --> 0) {
		a.read();
		b.read();
		c.read();
		d.read();

		cout << (intersect(a, b, c, d) ? "YES\n" : "NO\n");
	}

	return 0;
}
