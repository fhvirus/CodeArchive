#include <bits/stdc++.h>
using namespace std;
 
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
 
	int n;
	cin >> n;
 
	vector<int> x(n + 1, 0);
	for (int i = 1; i <= n; ++i)
		cin >> x[i];
 
	// O(n log n) 的作法狀態不太一樣
	// dp[i][j] 代表 x_1 ~ x_i 項的所有 increasing subsequence 裡
	// 長度為 j 的 IS 結尾最小可以是多少
	// 有點 greedy 的感覺
	
	vector<int> dp(n + 1, INT_MAX);
	dp[0] = 0;
 
	for (int i = 1; i <= n; ++i) {
		// dp 一定是遞增的，
		// 所以可以二分搜最早可以接上的位置
		int p = lower_bound(begin(dp), end(dp), x[i]) - begin(dp);
		dp[p] = x[i];
	}
 
	int ans = 0;
	// 記得判斷 ans + 1 會戳出去的狀況
	while (ans < n and dp[ans + 1] != INT_MAX)
		ans += 1;
 
	cout << ans << '\n';
 
	// 試著把過程畫出來看看吧！
	return 0;
}
