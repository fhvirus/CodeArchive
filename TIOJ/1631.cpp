#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
using namespace std;

#ifdef OWO
namespace Interactor {
#define x first
#define y second
	typedef long long ll;
	typedef pair<int, int> pii;
	const int kN = 50005;
	bool initialized = false;
	int cnt[2], ptr[2];
	pii pos[2][kN];
	int ecnt[2];
	pii edges[2][kN];
	struct DSU {
		vector<int> f; int cc;
		DSU() {}
		void init(int n) {
			f.assign(n+1, 0); cc = n;
			for (int i = 1; i <= n; ++i)
				f[i] = i;
		}
		int F(int u) { return u == f[u] ? u : f[u] = F(f[u]); }
		bool M(int u, int v) {
			u = F(u); v = F(v);
			if (u == v) return false;
			f[v] = u; --cc;
			return true;
		}
	} dsu[2];
	ll cross(pii a, pii b){
		return (a.x * b.y - a.y * b.x);
	}
	ll dot(pii a, pii b){
		return a.x * b.x + a.y * b.y;
	}
	pii vec(pii a, pii b){
		return {b.x - a.x, b.y - a.y};
	}
	ll sign(ll a){
		return a < 0 ? -1 : (a > 0 ? 1 : 0);
	}
	bool intersect(pii p1, pii p2, pii q1, pii q2){
		return (sign(cross(vec(p1, q1), vec(p1, q2))) * sign(cross(vec(p2, q1), vec(p2, q2))) < 0 and sign(cross(vec(q1, p1), vec(q1, p2))) * sign(cross(vec(q2, p1), vec(q2, p2))) < 0);
	}
}
void Init(int &gCnt, int &rCnt) {
	using namespace Interactor;
	if (initialized) {
		cout << "\033[1;31mWA: Already initialized\n\033[0m";
		exit(0);
	}
	cin.tie(0) -> sync_with_stdio(0);
	for (int color = 0; color < 2; ++color) {
		cin >> cnt[color];
		for (int i = 1; i <= cnt[color]; ++i)
			cin >> pos[color][i].first >> pos[color][i].second;
	}
	gCnt = cnt[0];
	rCnt = cnt[1];

	ptr[0] = 0;
	ptr[1] = 0;
	ecnt[0] = 0;
	ecnt[1] = 0;
	initialized = true;
	return;
}
void Get(int color, int &x, int &y) {
	using namespace Interactor;
	if (!initialized) {
		cout << "\033[1;31mWA: Not initialized\n\033[0m";
		exit(0);
	}
	if (ptr[color] == cnt[color]) {
		cout << "\033[1;31mWA: Get color " << color << " too many times\n\033[0m";
		exit(0);
	}
	++ptr[color];
	x = pos[color][ptr[color]].first;
	y = pos[color][ptr[color]].second;
	return;
}
void Report(int color, int n1, int n2) {
	using namespace Interactor;
	if (!initialized) {
		cout << "\033[1;31mWA: Not initialized\n\033[0m";
		exit(0);
	}
	if (ecnt[color] == cnt[color] - 1) {
		cout << "\033[1;31mWA: Add edge to color " << color << " too many times\n\033[0m";
		exit(0);
	}
	++ecnt[color];
	edges[color][ecnt[color]].first = n1;
	edges[color][ecnt[color]].second = n2;
}
void Finish(void) {
	using namespace Interactor;
	if (!initialized) {
		cout << "\033[1;31mWA: Not initialized\n\033[0m";
		exit(0);
	}
	for (int color = 0; color < 2; ++color)
		if (ecnt[color] != cnt[color] - 1) {
			cout << "\033[1;31mWA: Color " << color << " has too few edges\n\033[0m";
			exit(0);
		}
	for (int color = 0; color < 2; ++color) {
		dsu[color].init(cnt[color]);
		for (int i = 1; i <= ecnt[color]; ++i) {
			int n1 = edges[color][i].first;
			int n2 = edges[color][i].second;
			if (!dsu[color].M(n1, n2)) {
				cout << "\033[1;31mWA: Color " << color << ", Point " << n1 << " and " << n2 << " already connected\n\033[0m";
				exit(0);
			}
		}
		if (dsu[color].cc != 1) {
			cout << "\033[1;31mWA: Color " << color << " is not fully connected\n\033[0m";
			exit(0);
		}
	}
	for (int i = 1; i <= ecnt[0]; ++i)
		for (int j = 1; j <= ecnt[1]; ++j) {
			int g1 = edges[0][i].first;
			int g2 = edges[0][i].second;
			int r1 = edges[1][i].first;
			int r2 = edges[1][i].second;
			if (intersect (pos[0][g1], pos[0][g2], pos[1][r1], pos[1][r2])) {
				cout << "\033[1;31mWA: Edge " << i << " and edge " << j << " intersected\n\033[0m";
				exit(0);
			}
		}
	cout << "\033[1;32mAC\n\033[0m";
	exit(0);
}
#else
#include "lib1631.h"
#endif

typedef long long ll;

struct Point {
	int x, y, color, id;
	Point() {}
	Point (int _x, int _y, int _color, int _id):
		x(_x), y(_y), color(_color), id(_id) {}
	void get(int _color, int _id) {
		color = _color;
		id = _id;
		Get(color, x, y);
	}
};

// https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
ll cross (Point &o, Point &a, Point &b) { return (ll) (a.x - o.x) * (b.y - o.y) - (ll) (b.x - o.x) * (a.y - o.y); }
bool inTriangle (Point p, Point a, Point b, Point c) {
	ll d1 = cross(a, b, p);
	ll d2 = cross(b, c, p);
	ll d3 = cross(c, a, p);
	bool neg = (d1 < 0) or (d2 < 0) or (d3 < 0);
	bool pos = (d1 > 0) or (d2 > 0) or (d3 > 0);
	return !(neg and pos);
}

random_device rd;
mt19937 mt(rd());

void solve(array<vector<Point>, 2> &pts, Point g, Point r, Point a, int col) {
	if (pts[0].empty() and pts[1].empty()) return;
	for (int c: {0, 1}) if (pts[c ^ 1].empty()) {
		for (Point &p: pts[c])
			Report(c, (c ? r.id : g.id), p.id);
		return;
	}

	int np = mt() % pts[col ^ 1].size();
	Point pp = pts[col ^ 1][np];
	swap(pts[col ^ 1][np], pts[col ^ 1].back());
	pts[col ^ 1].pop_back();
	Report(col ^ 1, (col ^ 1 ? r.id : g.id), pp.id);

	array<vector<Point>, 2> goA, goB, goC;
	for (int c: {0, 1}) for (Point &p: pts[c]) {
		if (inTriangle(p, g, r, pp))
			goA[p.color].push_back(p);
		else if (inTriangle(p, g, a, pp))
			goB[p.color].push_back(p);
		else
			goC[p.color].push_back(p);
	}

	solve(goA, g, r, pp, pp.color);
	if (pp.color == 0) {
		solve(goB, g, a, pp, 0);
		solve(goC, pp, r, a, 1);
	} else {
		solve(goB, g, pp, a, 0);
		solve(goC, a, r, pp, 1);
	}
}

int main () {
	int g, r; Init(g, r);
	Point g1; g1.get(0, 1); // (0, s)
	Point g2; g2.get(0, 2); // (s, s)
	Point r1; r1.get(1, 1); // (0, 0)
	Point r2; r2.get(1, 2); // (s, 0)
	vector<Point> gp(g - 2), rp(r - 2);
	for (int i = 3; i <= g; ++i) gp[i - 3].get(0, i);
	for (int i = 3; i <= r; ++i) rp[i - 3].get(1, i);

	array<vector<Point>, 2> goLeft;
	array<vector<Point>, 2> goRight;
	for (auto &v: {gp, rp})
		for (auto &p: v) {
			if (inTriangle(p, g1, r1, r2))
				goLeft[p.color].push_back(p);
			else
				goRight[p.color].push_back(p);
		}

	Report(0, 1, 2);
	Report(1, 1, 2);

	solve(goLeft, g1, r1, r2, 1);
	solve(goRight, g1, r2, g2, 0);

	Finish();
}
