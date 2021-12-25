#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

struct Line {
	ll m, k;
	Line(ll _m, ll _k): m(_m), k(_k) {}
	ll operator() (ll x) { return m * x + k; }
};

// returns if intersection of (a, c) if before (b, c)
bool cmp(Line &a, Line &b, Line &c) {
	if (a.m == b.m) return a.k <= b.k;
	ll dm1 = a.m - c.m, dk1 = -(a.k - c.k);
	ll dm2 = a.m - b.m, dk2 = -(a.k - b.k);
	return dk1 * dm2 <= dk2 * dm1;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n, x; cin >> n >> x;
	vector<int> s(n+1, 0);
	vector<int> f(n+1, 0);
	for (int i = 1; i <= n; ++i) cin >> s[i];
	for (int i = 1; i <= n; ++i) cin >> f[i];
	f[0] = x;

	vector<ll> dp(n+1, INF);
	dp[0] = 0;

	deque<Line> sc;
	sc.emplace_back(f[0], dp[0]);

	for (int i = 1; i <= n; ++i) {
		while (sc.size() > 1 and sc[0](s[i]) >= sc[1](s[i])) sc.pop_front();
		dp[i] = sc[0](s[i]);
		Line cur(f[i], dp[i]);
		while (sc.size() > 1 and cmp(end(sc)[-2], end(sc)[-1], cur)) sc.pop_back();
		if (!(sc.back().m == cur.m and sc.back().k <= cur.k)) sc.push_back(cur);
	}

	cout << dp[n] << '\n';

	return 0;
}
