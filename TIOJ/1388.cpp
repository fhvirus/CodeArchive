#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	char ans = 0, c = readchar();
	while(c<'0'&&c!=EOF) c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

long long n, dp[101][101];
inline long long max(long long a, long long b){
	return a > b ? a : b;
}

int main(){
	while((n = R()) != 0){
		FOR(i, n) FOR(j, n) dp[i][j] = 0;
		FOR(i, n) dp[i][i] = R();
		for(int len = 2; len <= n; ++len){
			for(int l = 1, r = l + len - 1; r <= n; ++l, ++r){
				for(int k = l; k < r; ++k){
					dp[l][r] = max(dp[l][r], (
						(len&1) ?
						dp[l][k] * dp[k+1][r] :
						dp[l][k] + dp[k+1][r]
					));
				}
			}
		}
		printf("%lld\n", dp[1][n]);
	}
}