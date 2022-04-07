#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n;
	cin >> n;

	vector<vector<int>> c(2, vector<int>(n + 1, 0));
	for (auto& v: c) {
		for (int i = 1; i <= n; ++i) {
			cin >> v[i];
			v[i] += v[i - 1];
		}
	}

	vector<int> t(n + 1, 0);
	for (int i = 1; i <= n; ++i)
		cin >> t[i];

	struct Triple {
		int a, b, c;
		Triple(int a, int b, int c): a(a), b(b), c(c) {}
	};

	vector<vector<int>> dp(2, vector<int>(n + 1, INT_MAX));
	dp[0][0] = dp[1][0] = 0;

	array<vector<Triple>, 2> stk;

	int ans = INT_MAX;
	for (int i = 1; i <= n; ++i) {
		for (int k: {0, 1}) {
			int a = dp[k][i - 1] - (i > 1 ? c[k][i - 2] : 0);
			int b = c[k][i - 1] + t[i - 1];
			while (!stk[k].empty() and stk[k].back().b <= b) {
				a = min(a, stk[k].back().a);
				stk[k].pop_back();
			}
			int mnv = min(a + b, !stk[k].empty() ? stk[k].back().c : INT_MAX);
			stk[k].emplace_back(a, b, mnv);
			dp[k ^ 1][i] = mnv;
			ans = min(ans, mnv + (c[k ^ 1][n] - c[k ^ 1][i - 1]));
		}
	}

	cout << ans << '\n';

	return 0;
}
