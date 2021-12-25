#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

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
	auto f = [&](int j, int i) {
		return dp[j] + (pre[i] - pre[j]) * (pre[i] - pre[j]);
	};
	auto solve = [&](ll penalty) {
		dp.assign(n+1, INF); dp[0] = 0;
		sc.assign(n+1, INF); sc[0] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < i; ++j) {
				ll cur = f(j, i) + penalty;
				if (dp[i] > cur) {
					dp[i] = cur;
					sc[i] = sc[j] + 1;
				} else if (dp[i] == cur)
					sc[i] = min(sc[i], sc[j] + 1);
			}
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
