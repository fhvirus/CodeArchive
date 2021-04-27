#include<iostream>
#include<algorithm>
using namespace std;

int m, n;
int a[52][10002];
int dp[2][52][10002];

int main(){
	cin >> m >> n;
	for(int i = 1; i <= m + 1; ++i)
		for(int j = 0; j <= n + 1; ++j)
			dp[0][i][j] = dp[1][i][j] = -2147483647;
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= n; ++j)
			cin >> a[i][j];
	for(int i = 1; i <= m + 1; ++i){
		for(int j = 1; j <= n; ++j)
			dp[0][i][j] = a[i][j] + max(dp[0][i][j-1], max(dp[0][i-1][j], dp[1][i-1][j]));
		for(int j = n; j >= 1; --j)
			dp[1][i][j] = a[i][j] + max(dp[1][i][j+1], max(dp[0][i-1][j], dp[1][i-1][j]));
	}
	int ans = -2147483647;
	for(int j = 1; j <= n; ++j)
		ans = max(ans, max(dp[0][m+1][j], dp[1][m+1][j]));
	cout << ans;
}