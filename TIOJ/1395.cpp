#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0'&&c!=EOF) c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
const int N = 33000;
int n = 1, in, a[N+1], dp[N+1];
inline int min(int a, int b, int c){
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}
bool lastiszero = false;
signed main(){
	while(true){
		while(true){
			if((in = R()) == 0){
				if(lastiszero) return 0;
				lastiszero = true;
				break;
			}
			lastiszero = false;
			a[n++] = in;
		}
		a[n] = 0;
		dp[0] = 0;
		dp[1] = 10 + a[1];
		dp[2] = 20 + a[2];
		for(int i = 3; i <= n; ++i)
			dp[i] = min(dp[i-1] + 10, dp[i-2] + 20, dp[i-3] + 30) + a[i];
		printf("%lld\n", dp[n] * 10);
		n = 1;
	}
	return 0;
}