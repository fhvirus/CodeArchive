#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline int R2(){
	char c = readchar();
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	return c == '-' ? -(readchar() - '0') : c - '0';
}

const int N = 3001;
int m, n, dp[N], a, left, cur, ans;
inline int max(int a, int b){
	return a > b ? a : b;
}
inline int max(int a, int b, int c){
	return a > b ? a > c ? a : c : b > c ? b : c;
}

int main(){
	m = R(), n = R();
	FOR(i,m){
		left = 0;
		FOR(j,n){
			a = R2();
			cur = max(0, left, dp[j]) + a;
			ans = max(ans, cur);
			dp[j-1] = left;
			left = cur;
		}
		dp[n] = cur;
	}
	printf("%d\n", ans);
}