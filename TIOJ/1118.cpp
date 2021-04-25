#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char s[20], t[20];
int n, m, dp[20][20];
int main(){
	while(fgets(s + 1, 20, stdin)){
		fgets(t + 1, 20, stdin);
		n = strlen(s + 1) - 1;
		m = strlen(t + 1) - 1;
		for(int i = 1; i <= n; ++i) dp[i][0] = -3 * i;
		for(int i = 1; i <= m; ++i) dp[0][i] = -3 * i;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j){
				if(s[i] == t[j]) dp[i][j] = max({
					dp[i-1][j-1] + 10,
					dp[i-1][j] - 3,
					dp[i][j-1] - 3
				});
				else dp[i][j] = max({
					dp[i-1][j-1] - 5,
					dp[i-1][j] - 3,
					dp[i][j-1] - 3
				});
			}
		printf("%.2lf%%\n", dp[n][m] * 10.0 / n);
	}
}