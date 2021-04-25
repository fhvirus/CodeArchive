#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<unistd.h>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<14;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
#define ll long long
inline ll max(ll a, ll b){
	return a > b ? a : b;
}
const int N = 2001;
int n, m, h[N], c[N], jizz, a, b;
ll dp[N];
char outbuf[20], eek[20];
int outp, eekp;
inline void W(ll n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    write(1, outbuf, outp);
}

int main(){
	n = R(), m = R();
	FOR(i, n){
		a = R(), b = R();
		if(jizz != 0 and h[jizz-1] <= a and c[jizz-1] >= b) --jizz;
		h[jizz] = a, c[jizz] = b, ++jizz;
	}
	for(int i = 0; i < jizz; ++i){
		for(int j = c[i]; j <= m; ++j) dp[j] = max(dp[j - c[i]] + h[i], dp[j]);
	}
	W(dp[m]);
}