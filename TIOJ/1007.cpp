#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
typedef unsigned long long ull;

ull n, m, dp[100];

int main(){
	scanf("%llu %llu", &n, &m);
	dp[0] = 1;
	for(int i = 1; i <= n; ++i)
		dp[i] = dp[i-1]<<1;
	dp[n+1] = (dp[n]<<1)-1;
	for(int i = n+2; i <= m; ++i)
		dp[i] = (dp[i-1]<<1) - dp[i-n-2];
	printf("%llu", dp[m]);
}