#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
void mad(int &u, int v) {
	u += v - MOD;
	u += MOD & (u >> 31);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	string A, B;
	cin >> A >> B;

	int n = A.size(), m = B.size();

	vector<vector<int>> nxt(m + 1, vector<int>(26, m + 1));
	for (int i = m; i >= 1; --i) {
		nxt[i - 1] = nxt[i];
		nxt[i - 1][B[i - 1] - 'a'] = i;
	}

	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	dp[0][0] = 1;

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			for (int c = 0; c < 26; ++c) {
				int ni = i + (i < n and A[i] - 'a' == c), nj = nxt[j][c];
				if (nj > m) continue;
				mad(dp[ni][nj], dp[i][j]);
			}
		}
	}

	int ans = 0;
	for (int j = 0; j <= m; ++j)
		mad(ans, dp[n][j]);

	cout << ans << '\n';

	return 0;
}
