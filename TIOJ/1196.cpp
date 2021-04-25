#include<cstdio>
int n;
char g[11][12];
int dp[11][11];
inline int max(int a, int b){
	return a > b ? a : b;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%s", g[i]+1), dp[i][0] = dp[0][i] = -1;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j){
			if(g[i][j] == 'X') dp[i][j] = -1;
			else if(g[i][j] == 'A') dp[i][j] = 0;
			else if(g[i][j] <= '9' and g[i][j] >= '0') dp[i][j] = (max(dp[i-1][j], dp[i][j-1]) == -1 ? -1 : max(dp[i-1][j], dp[i][j-1]) + g[i][j] - '0');
			else dp[i][j] = (max(dp[i-1][j], dp[i][j-1]) == -1 ? -1 : max(dp[i-1][j], dp[i][j-1]));
		}
	if(dp[n][n] == -1) putchar('X');
	else printf("%d\n", dp[n][n]);
}