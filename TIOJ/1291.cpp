#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<unistd.h>
#define FOR(i,n) for(int i=1;i<=n;++i)
const int S = 1<<14;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) write(1, outbuf, outp), outp = 0;
}


#define N 201
#define M 1000000
int n, m, ans, dp[N][N] = {1};

int main(){
	while(n = R(), m = R(), n != 0){
		ans = 0;
		FOR(i, n) FOR(j, m) dp[i][j] = (dp[i-1][j-1] + dp[i][j-1] * i) % M;
		FOR(i, n) ans = (ans + dp[i][m]) % M;
		W(ans);
	}
	write(1, outbuf, outp);
}