#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
struct Vec {
	double x, y;
	Vec(double x = 0, double y = 0): x(x), y(y) {}
	void read() { cin >> x >> y; }
};

#define opab(x) operator x (Vec a, Vec b)
Vec opab(+) { return Vec(a.x + b.x, a.y + b.y); }
Vec opab(-) { return Vec(a.x - b.x, a.y - b.y); }
double opab(*) { return (a.x * b.x + a.y * b.y); }
double opab(^) { return (a.x * b.y - a.y * b.x); }
double abs2(Vec a) { return a * a; }
double abs(Vec a) { return sqrt(a * a); }

int sign(double a) { return fabs(a) < eps ? 0 : (a > 0) - (a < 0); }
int ori(Vec o, Vec a, Vec b) { return sign((a - o) ^ (b - o)); }
bool colinear(Vec a, Vec b, Vec c) { return ori(c, a, b) == 0; }
bool online(Vec a, Vec b, Vec c) { return colinear(a, b, c) and sign((a - c) * (b - c)) <= 0; }
bool intersect(Vec a, Vec b, Vec c, Vec d) {
	if (online(a, b, c) or online(a, b, d) or online(c, d, a) or online(c, d, b))
		return true;
	return ori(a, b, c) * ori(a, b, d) <= 0 and
		ori(c, d, a) * ori(c, d, b) <= 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int t;
	cin >> t;

	while (t --> 0) {
		Vec a, b, c;
		a.read();
		b.read();
		c.read();

		if (colinear(a, b, c)) cout << "TOUCH\n";
		else if (ori(a, b, c) > 0) cout << "LEFT\n";
		else cout << "RIGHT\n";
	}

	return 0;
}
