#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

int n, a[21][21], b[21], dp[21][21];

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	while(true){
		n = R();
		if(n == 0) break;
		a[1][1] = R();
		for(int j = 2; j <= n; ++j)
			a[j][1] = a[1][1] + j;
		for(int i = 1; i <= n; ++i){
			for(int j = 2; j <= n; ++j){
				a[i][j] = a[i][j-1] * 17 % 103 * (((i+j)&1)?-1:1);
			}
		}

		for(int i = 2; i <= n; ++i){
			for(int j = 1; j <= n; ++j){
				a[i][j] += a[i-1][j];
			}
		}

		int ans = 0, mx, sum;
		for(int u = 1; u <= n; ++u){
			for(int d = u+1; d <= n; ++d){
				for(int i = 1; i <= n; ++i)
					b[i] = a[u][i] - a[d-1][i];
				for(int i = 1; i <= n; ++i)

					ans = max(ans, mx);
			}
		}
	}
}