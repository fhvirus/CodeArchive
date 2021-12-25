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

	vector<ll> sc(n+1, INF); sc[0] = 0;
	vector<ll> dp(n+1, INF); dp[0] = 0;
	for (int l = 1; l <= k; ++l) {
		deque<Line> dq;
		dq.emplace_back(-2ll * pre[0], sc[0] + pre[0] * pre[0]);
		for (int i = 1; i <= n; ++i) {
			while (dq.size() > 1 and dq[0](pre[i]) > dq[1](pre[i])) dq.pop_front();
			dp[i] = dq[0](pre[i]) + pre[i] * pre[i];
			Line cur(-2ll * pre[i], sc[i] + pre[i] * pre[i]);
			while (dq.size() > 1 and cmp(end(dq)[-2], end(dq)[-1], cur)) dq.pop_back();
			dq.push_back(cur);
		}
		swap(dp, sc);
	}
	cout << sc[n] << '\n';
  return 0;
}
