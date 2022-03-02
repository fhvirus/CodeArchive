#include <bits/stdc++.h>
using namespace std;

int main() {

	int n; cin >> n;
	vector<int> dp(n + 1, 0);
	dp[1] = 1;
	for (int i = 2; i <= n; ++i)
		for (int j = i; j >= 1; --j)
			dp[j] = (dp[j - 1] + 1ll * dp[j] * j) % 100'000'007;
	cout << accumulate(begin(dp), end(dp), 0ll) % 100'000'007 << '\n';

	return 0;
}
