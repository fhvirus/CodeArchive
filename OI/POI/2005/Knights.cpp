#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	auto extgcd = [&](const auto& extgcd, int a, int b, int& x, int& y, int& d) -> void {
		if (b == 0) {
			x = 1;
			y = 0;
			d = a;
			return;
		}
		extgcd(extgcd, b, a % b, y, x, d);
		y -= a/b * x;
		return;
	};

	typedef pair<int, int> Vec;
	auto solve = [&](Vec u, Vec v, Vec& a, Vec& b) -> void {
		if (u.first == 0) {
			a = u;
			b = v;
			return;
		}
		if (v.first == 0) {
			a = v;
			b = u;
			return;
		}
		int p, q, d;
		extgcd(extgcd, u.first, v.first, p, q, d);
		a = Vec(0, abs(v.first * u.second - u.first * v.second) / d);
		b = Vec(d, u.second * p + v.second * q);
	};

	int n;
	cin >> n;

	vector<Vec> vs(n);
	for (Vec& v: vs)
		cin >> v.first >> v.second;

	Vec a, b;
	solve(vs[0], vs[1], a, b);

	for (int i = 2; i < n; ++i) {
		Vec tmp = a;
		solve(vs[i], b, a, b);
		a.second = gcd(a.second, tmp.second);
	}

	cout << a.first << ' ' << a.second << '\n';
	cout << b.first << ' ' << b.second << '\n';

	return 0;
}
