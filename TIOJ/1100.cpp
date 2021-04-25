#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], jeek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) jeek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = jeek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}
inline int min(int a, int b){
	return a < b ? a : b;
}
inline int max(int a, int b){
	return a > b ? a : b;
}

const int INF = 8e7;
int n, dp[2][1001], roll, bound, owo;

int main(){
	while((n = R()) != 0){
		int r, d, p;
		dp[1-roll][0] = dp[roll][0] = 0;
		for(int i = 1; i <= n; ++i)
			dp[1][i] = dp[0][i] = INF;

		bound = 1;
		for(int i = 1; i <= n; ++i){
			r = R(), d = R(), p = R();
			int j = 1;
			for(; j <= bound + 1; ++j){
				if(max(dp[1-roll][j-1], r - 1) + p <= d)
					dp[roll][j] = min(dp[1-roll][j], max(dp[1-roll][j-1], r - 1) + p);
				else dp[roll][j] = dp[1-roll][j];
			}
			if(dp[roll][bound + 1] != INF) ++bound;
			roll = 1 - roll;
		}
		W(bound);
	}
	fwrite(outbuf, 1, outp, stdout);
}