#include <iostream>
using namespace std;

typedef long long ll;
const int kN = 5005;
const ll INF = 1e18;
int n, x[kN];
ll pre[kN];

ll dp[kN][kN];
int sc[kN][kN];

signed main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> x[i];

	for (int i = 1; i <= n; ++i)
		pre[i] = pre[i-1] + x[i];

	for (int i = 1; i + 1 <= n; ++i)
		dp[i][i + 1] = x[i] + x[i + 1];
	for (int i = 1; i + 1 <= n; ++i)
		sc[i][i + 1] = i;

	for (int len = 3; len <= n; ++len) {
		for (int l = 1, r = l + len - 1; r <= n; ++l, ++r) {
			int tl = sc[l][r-1];
			int tr = sc[l+1][r];
			ll val = INF;
			int pos = tl;
			for (int i = tl; i <= tr; ++i) {
				ll cur = dp[l][i] + dp[i + 1][r];
				if (val > cur) {
					val = cur;
					pos = i;
				}
			}
			dp[l][r] = val + pre[r] - pre[l - 1];
			sc[l][r] = pos;
		}
	}

	cout << dp[1][n] << '\n';

	return 0;
}
