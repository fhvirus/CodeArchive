#include <algorithm>
#include <iostream>
using namespace std;

// Keywords:
// Knuth's optimization
// Quadrangle inequalities

typedef long long ll;
const int kN = 3003;
const ll INF = 1e18;

int n, k, c[kN];
ll cnt[kN], pre[kN];
ll f(int l, int r) {
	int m = (l + r) / 2;
	return (pre[m] - pre[l]) - l * (cnt[m] - cnt[l])
		+ r * (cnt[r] - cnt[m]) - (pre[r] - pre[m]);
}

ll dp[kN], sc[kN];
void solve(int l, int r, int tl, int tr) {
	if (l > r) return;
	int m = (l + r) / 2;
	ll val = INF;
	int pos = -1;
	for (int i = tl; i <= min(m, tr); ++i) {
		ll cur = sc[i] + f(i, m);
		if (val > cur) {
			val = cur;
			pos = i;
		}
	}
	dp[m] = val;
	solve(l, m-1, tl, pos);
	solve(m+1, r, pos, tr);
}

signed main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		cin >> c[i];

	for (int i = 1; i <= n; ++i) {
		cnt[i] = cnt[i-1] + c[i];
		pre[i] = pre[i-1] + (ll) i * c[i];
	}

	for (int i = 1; i <= n; ++i)
		sc[i] = i * cnt[i] - pre[i];

	for (int l = 2; l <= k; ++l) {
		solve(1, n, 1, n);
		swap(dp, sc);
	}

	ll ans = INF;
	for (int i = 1; i <= n; ++i)
		ans = min(ans, sc[i] + (pre[n] - pre[i]) - i * (cnt[n] - cnt[i]));
	cout << ans << '\n';

  return 0;
}
