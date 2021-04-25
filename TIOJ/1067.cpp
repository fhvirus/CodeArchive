#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<cstring>
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int readint(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline int gcd(int a, int b){
	while(b){
		a = a%b;
		a^=b^=a^=b;
	}
	return a;
}
inline int max(int a, int b){
	return a > b ? a : b;
}

int n, m, dp[2][10000], mx;
int main(){
	while(true){
		n = readint(), m = readint();
		if(n==0) return 0;
		memset(dp[0], 0, m<<2);
		memset(dp[1], 0, m<<2);
		for(int i = 0, a; i < n; ++i){
			a = readint();
			for(int j = 0; j < m; ++j)
				if(dp[0][j] or j==0)
					dp[1][(j*10+a)%m] = max(
						dp[1][(j*10+a)%m],
						dp[0][j] + 1
					);
			memcpy(dp[0], dp[1], m<<2);
		}
		mx = 0;
		for(int i = 0; i < m; ++i)
			if(gcd(i, m)==1) mx = max(mx, dp[1][i]);
		printf("%d\n", mx);
	}
	return 0;
}