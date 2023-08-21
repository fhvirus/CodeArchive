#include <bits/stdc++.h>
using namespace std;

#ifdef OWO
void Report(int x, double R) {
	cout << "ans: " << x << ' ' << R << '\n';
}
#else
#include "lib1747.h"
#endif

template <class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point (T x = 0, T y = 0): x(x), y(y) {}
#define op(x) operator x (const P& o) const
	P op(-) { return P(x - o.x, y - o.y); }
	T op(*) { return x * o.x + y * o.y; }
	T op(^) { return x * o.y - y * o.x; }
};

typedef long long ll;
typedef Point<ll> P;
inline int sign(ll a) { return (a > 0) - (a < 0); }

int ori(P a, P b, P c) { return sign((b - a) ^ (c - a)); }
bool cmp(P a, P b) {
	bool sa = (a.y > 0 or (a.y == 0 and a.x > 0));
	bool sb = (b.y > 0 or (b.y == 0 and b.x > 0));
	if (sa != sb) return sa > sb;
	return sign(a ^ b) > 0;
}

inline int nxt(int i, int n)
{ return i + 1 == n ? 0 : i + 1; }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	ll n;
	cin >> n;

	vector<P> ps(n), a(n - 1);
	for (P& p: ps) cin >> p.x >> p.y;

	ll ans = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j + 1 < n; ++j)
			a[j] = ps[j + (j >= i)] - ps[i];
		sort(begin(a), end(a), cmp);
		for (int j = 0, k = 1; j + 1 < n; ++j) {
			while (k != j and ori(a[j], a[k], P(0, 0)) >= 0) k = nxt(k, n - 1);
			ll num = k - j;
			if (num <= 0) num += n - 1;
			if (num >= 3) ans += (num - 1) * (num - 2) / 2;
		}
	}

	ll nC3 = n * (n - 1) * (n - 2) / 6;
	ll n1C3 = (n - 1) * (n - 2) * (n - 3) / 6;
	ll nC4 = n * (n - 1) * (n - 2) * (n - 3) / 24;

	ans = n1C3 * n - ans;

	Report(ps[0].x, 3 + (double) (2 * nC4 - ans) / nC3);

	return 0;
}
