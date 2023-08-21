#include <bits/stdc++.h>
using namespace std;

const int kS = 515;
int N, S, a[kS], b[kS], c[kS], dp[kS], sc[kS], ans[kS];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> N;

	while (N --> 0) {
		cin >> S;
		for (int i = 1; i <= S; ++i) cin >> a[i];
		for (int i = 1; i <= S; ++i) cin >> b[i];

		for (int i = 1; i <= S; ++i) {
			c[i] = S + 1;
			for (int j = 1; j <= S; ++j) {
				if (a[i] == b[j]) {
					c[i] = j;
					break;
				}
			}
		}

		int mxp = 0;
		int mxv = 0;

		for (int i = 1; i <= S; ++i) {
			if (c[i] == S + 1) continue;
			dp[i] = 1;
			sc[i] = 0;
			for (int j = 1; j < i; ++j) {
				if (c[j] != S + 1 and a[j] > a[i] and c[j] < c[i] and dp[i] < dp[j] + 1) {
					dp[i] = dp[j] + 1;
					sc[i] = j;
				}
			}
			if (dp[i] > mxv) {
				mxv = dp[i];
				mxp = i;
			}
		}

		for (int i = mxp, j = mxv; i != 0; i = sc[i])
			ans[j--] = a[i];

		for (int i = 1; i <= mxv; ++i)
			cout << ans[i] << ' ';
		cout << '\n';
	}

	return 0;
}
