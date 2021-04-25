#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
inline char readchar(){
	const int S = 1<<18;
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF: *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline bool G(){
	char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	return c < '2';
}
inline int max(int a, int b){
	return a > b ? a : b;
}
inline int min(int a, int b, int c){
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

#include<cstring>
int l, w, dp[5001], ans;

int main(){
	while(true){
		l = R(); w = R();
		if(l == 0) break;

		ans = 0;
		memset(dp, 0, sizeof(dp));
		
		for(int i = 1; i <= l; ++i){
			int a = dp[0], b;
			for(int j = 1; j <= w; ++j){
				if(G()) b = min(dp[j-1], dp[j], a) + 1,
						ans = max(ans, b);
				else b = 0;
				dp[j-1] = a;
				a = b;
			}
			dp[w] = a;
		}

		printf("%d\n", ans * ans);
	}
	return 0;
}