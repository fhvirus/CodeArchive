#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
const int S = 1<<19;
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

const int N = 51;
int n, m, a[N][N], ans;
inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	while((n = R()) != 0){
		m = R(), ans = -2147483648;
		FOR(i, n) FOR(j, m) a[i][j] = R() + a[i][j-1];
		FOR(l, m) for(int r = l; r <= m; ++r){
			int dp = -2147483648;
			FOR(i, n)
				dp = max(dp, 0) + a[i][r] - a[i][l-1],
				ans = max(ans, dp);
		}
		printf("%d\n", ans);
	}
}