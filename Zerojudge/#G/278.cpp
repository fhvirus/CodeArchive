#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, k;
	cin >> n >> k;

	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i)
		cin >> a[i];

	// can_go[i]: 以 i 為右界，一個合法區間最左邊可以到哪
	vector<int> last_id(n + 1, 0);
	vector<int> can_go(n + 1, 1);
	for (int i = 1; i <= n; ++i) {
		can_go[i] = max(can_go[i-1], last_id[a[i]] + 1);
		last_id[a[i]] = i;
	}

	vector<int> dp(n + 1, 0), sc(n + 1, 0);
	for (int i = 0; i < k; ++i) {
		for (int j = 1; j <= n; ++j) {
			dp[j] = max(dp[j-1], sc[can_go[j] - 1] + (j - can_go[j] + 1));
		}
		swap(dp, sc);
	}

	// 最後會被多 swap 一次
	cout << sc[n] << '\n';
	return 0;
}
