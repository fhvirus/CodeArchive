#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<14;
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c=readchar();
	while(c<'0')c=readchar();
	while(c>='0')ans=(ans*10)+(c^'0'),c=readchar();
	return ans;
}
inline int max(int a, int b){ return a > b ? a : b;}

const int N = 1000;
int T, w, b, n, a[N], d[N], m;
int dp[10001];

int main(){
	T = R();
	for(; T; --T){
		w = R(), b = R(), n = R();
		FOR(i, w) dp[i] = 0;
		FOR(i, n) a[i] = R(), d[i] = R();
		m = R();
		FOR(i, n){
			a[i] += m;
			for(int j = a[i]; j < w; ++j){
				dp[j] = dp[j - a[i]] + d[i];
			}
			if(dp[w-1] >= b) break;
		}
		puts(dp[w-1] >= b ? "Yes" : "No");
	}
}