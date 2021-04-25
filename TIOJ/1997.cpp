#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#define ll long long
const int N = 1e6 + 1;
int n, K, a;
ll dp[7][N];
int p[7][N];

int main(){
	n = R(), K = R() - 1;
	FOR(i, n){
		a = R();
		dp[0][i] = dp[0][i-1] + a;
		for(int k = 1; k <= K and k < i; ++k){
			int t = (k & 1 ? -1 : 1);
			if(k == i-1){
				p[k][i] = i;
				dp[k][i] = dp[k-1][i-1] + t * a;
			} else if(dp[k][i-1] + t * a >= dp[k-1][i-1] + t * a){
				p[k][i] = p[k][i-1];
				dp[k][i] = dp[k][i-1] + t * a;
			} else {
				p[k][i] = i;
				dp[k][i] = dp[k-1][i-1] + t * a;
			}
		}
	}
	while(K != 0){
		printf("%d\n", p[K][n] - 1);
		n = p[K--][n] - 1;
	}
}