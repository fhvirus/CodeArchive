#include<bits/stdc++.h>
using namespace std;

struct Vec {
	int64_t x, y;
	Vec (int64_t x = 0, int64_t y = 0): x(x), y(y) {}
	void read() { cin >> x >> y; }
};

bool operator < (const Vec& a, const Vec& b)
{ return a.x != b.x ? a.x < b.x : a.y < b.y; }
Vec operator + (const Vec& a, const Vec& b)
{ return Vec(a.x + b.x, a.y + b.y); }
Vec operator - (const Vec& a, const Vec& b)
{ return Vec(a.x - b.x, a.y - b.y); }
Vec operator - (const Vec& a)
{ return Vec(-a.x, -a.y); }
int64_t operator * (const Vec& a, const Vec& b)
{ return a.x * b.x + a.y * b.y; }
int64_t operator ^ (const Vec& a, const Vec& b)
{ return a.x * b.y - a.y * b.x; }
int sign(int64_t a) { return (a > 0) - (a < 0); }
int ori(const Vec& a, const Vec& b, const Vec& c)
{ return sign((b - a) ^ (c - a)); }
bool right(const Vec& a)
{ return a.x > 0 or (a.x == 0 and a.y > 0); }
bool cmp(const Vec& a, const Vec& b) {
	bool u = right(a), v = right(b);
	if (u != v) return u > v;
	return (a ^ b) > 0;
}

void getHull(vector<Vec>& ps) {
	if (ps.size() <= 1) return;
	sort(begin(ps), end(ps));
	vector<Vec> stk;
	int n = ps.size();
	for (int i = 0; i < n; ++i) {
		while (stk.size() > 1 and ori(end(stk)[-2], end(stk)[-1], ps[i]) <= 0)
			stk.pop_back();
		stk.push_back(ps[i]);
	}
	int t = stk.size();
	for (int i = n - 2; i >= 0; --i) {
		while (stk.size() > t and ori(end(stk)[-2], end(stk)[-1], ps[i]) <= 0)
			stk.pop_back();
		stk.push_back(ps[i]);
	}
	stk.pop_back();
	swap(ps, stk);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int N;
	cin >> N;

	Vec o(0, 0);
	vector<Vec> vs;

	for (int i = 0; i < N; ++i) {
		int G;
		cin >> G;

		vector<Vec> ps(G);
		for (Vec& v: ps)
			v.read();

		getHull(ps);
		int n = ps.size();

		o = o + ps[0];
		for (int i = 0; i + 1 < n; ++i)
			vs.push_back(ps[i + 1] - ps[i]);
		vs.push_back(ps[0] - ps[n - 1]);
	}

	sort(begin(vs), end(vs), cmp);

	int64_t ans = o * o;
	for (const Vec& v: vs) {
		o = o + v;
		ans = max(ans, o * o);
	}

	cout << ans << '\n';

	return 0;
}
