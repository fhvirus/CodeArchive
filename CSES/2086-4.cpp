#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

vector<ll> pre, sc, dp;
void solve(int l, int r, int tl, int tr) {
	if (l > r) return;
	int m = (l + r) / 2;
	ll val = INF;
	int pos = -1;
	for (int i = tl; i <= tr; ++i) {
		ll cur = sc[i] + (pre[m] - pre[i]) * (pre[m] - pre[i]);
		if (val > cur) {
			val = cur;
			pos = i;
		} else if (val == cur)
			pos = min(pos, i);
	}
	dp[m] = val;
	solve(l, m-1, tl, pos);
	solve(m+1, r, pos, tr);
}

signed main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int n, k; cin >> n >> k;
	vector<int> x(n+1, 0);
	for (int i = 1; i <= n; ++i)
		cin >> x[i];

	pre.assign(n+1, 0);
	for (int i = 1; i <= n; ++i)
		pre[i] = pre[i-1] + x[i];

	dp.assign(n+1, INF); dp[0] = 0;
	sc.assign(n+1, INF); sc[0] = 0;
	for (int i = 1; i <= n; ++i)
		sc[i] = pre[i] * pre[i];

	for (int l = 2; l <= k; ++l) {
		solve(1, n, 1, n);
		swap(dp, sc);
	}

	cout << sc[n] << '\n';
  return 0;
}
