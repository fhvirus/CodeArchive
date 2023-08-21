#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<float, int> pdi;

struct Vec
{ int x, y, id; };

bool ccw(const Vec& a, const Vec& b, const Vec& c)
{ return (ll) (b.x - a.x) * (c.y - a.y) >= (ll) (b.y - a.y) * (c.x - a.x); }

double dis(const Vec& a, const Vec& b)
{ return sqrt((ll) (a.x - b.x) * (a.x - b.x) + (ll) (a.y - b.y) * (a.y - b.y)); }

void make_hull(int N, vector<Vec>& pts) {
	vector<Vec> h(pts.size() + 1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(begin(pts), end(pts)))
		for (const Vec& p: pts) {
			while (t >= s + 2 and ccw(h[t-2], h[t-1], p)) --t;
			h[t++] = p;
		}
	h.resize(t);
	swap(pts, h);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N;

	cin >> N;

	vector<Vec> pts(N);

	for (int i = 0; i < N; ++i) {
		cin >> pts[i].x >> pts[i].y;
		pts[i].id = i;
	}

	make_hull(N, pts);

	vector dp(N, vector(N, pdi(1e18, -1)));

	for (int i = 0; i + 1 < N; ++i)
		dp[i][i+1] = pdi(dis(pts[i], pts[i+1]), -1);

	for (int l = N-3; l >= 0; --l) {
		for (int r = l + 2; r < N; ++r) {
			for (int m = l+1; m < r; ++m) {
				double d = dp[l][m].first + dp[m][r].first;
				if (d < dp[l][r].first) {
					dp[l][r].first = d;
					dp[l][r].second = m;
				}
			}
			dp[l][r].first += dis(pts[l], pts[r]);
		}
	}

	auto trace = <:&:>(const auto& trace, const int& l, const int& r) -> void {
		if (l + 1 == r) return;
		if (l != 0 or r != N-1)
			cout << pts[l].id << ' ' << pts[r].id << '\n';
		int m = dp[l][r].second;
		trace(trace, l, m);
		trace(trace, m, r);
	};

	trace(trace, 0, N-1);

	return 0;
}
