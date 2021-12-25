#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

struct Line {
	ll m, k;
	Line(): m(0), k(0) {}
	Line(ll _m, ll _k): m(_m), k(_k) {}
	ll operator() (ll x) { return m * x + k; }
};
bool cmp(Line &a, Line &b, Line &c) {
	ll dm1 = a.m - c.m, dk1 = -(a.k - c.k);
	ll dm2 = a.m - b.m, dk2 = -(a.k - b.k);
	return (__int128) dk1 * dm2 <= (__int128) dk2 * dm1;
}

signed main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n, k; cin >> n >> k;
	vector<int> x(n+1, 0);
	for (int i = 1; i <= n; ++i)
		cin >> x[i];

	vector<ll> pre(n+1, 0);
	for (int i = 1; i <= n; ++i)
		pre[i] = pre[i-1] + x[i];

	vector<ll> dp, sc;
	vector<Line> lines(n+1);
	auto f = [&](int j, int i) {
		return dp[j] + (pre[i] - pre[j]) * (pre[i] - pre[j]);
	};
	auto solve = [&](ll penalty) {
		dp.assign(n+1, INF); dp[0] = 0;
		sc.assign(n+1, INF); sc[0] = 0;
		deque<int> dq; dq.push_back(0);
		for (int i = 1; i <= n; ++i) {
			while(dq.size() > 1 and lines[dq[0]](pre[i]) > lines[dq[1]](pre[i])) dq.pop_front();
			dp[i] = lines[dq[0]](pre[i]) + penalty + pre[i] * pre[i];
			sc[i] = sc[dq[0]] + 1;
			lines[i] = Line(-2ll * pre[i], dp[i] + pre[i] * pre[i]);
			while (dq.size() > 1 and cmp(lines[end(dq)[-2]], lines[end(dq)[-1]], lines[i])) dq.pop_back();
			dq.push_back(i);
		}
	};

	ll lb = 0, rb = 1e18, mid;
	while (lb < rb) {
		mid = (lb + rb) / 2;
		solve(mid);
		if (sc[n] > k) lb = mid + 1;
		else rb = mid;
	}

	solve(lb);
	cout << dp[n] - k * lb << '\n';
  return 0;
}
