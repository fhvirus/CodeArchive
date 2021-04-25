#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<unistd.h>
const int S = 1<<10;
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
char outbuf[10], eek[10];
int outp, eekp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    write(1, outbuf, outp);
}
short n,dp[100],a,b,ans;
int main(){
	n = R();
	dp[0] = R();
	for(int i = 1; i < n; ++i){
		a = dp[0];
		dp[0] += R();
		for(int j = 1; j <= i; ++j){
			b = dp[j];
			dp[j] = R() + (a > b ? a : b);
			a = b;
			ans = (ans > dp[j] ? ans : dp[j]);
		}
	}
	W(ans);
	return 0;
}