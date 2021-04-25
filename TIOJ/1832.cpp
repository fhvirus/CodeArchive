#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#include<cstdio>
using ll = long long;
const int S = 1<<17;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p == q and (q = (p = buf) + fread(buf, 1, S, stdin)) == buf) return EOF;
	return *p++;
}
inline ll R(){
	ll ans = 0; char c = readchar();
	while((c > '9' or c < '0') and c != EOF) c = readchar();
	while(c <= '9' and c >= '0') ans = (ans<<3) + (ans<<1) + (c ^ '0'), c = readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
const ll INF = 1e18;
inline void W(ll n){
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = '\n'; return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

const int N = 1e6 + 1;
int n, q;
ll h[N];

int main(){
	n = R(); q = R();
	for(int i = 1; i <= n; ++i) h[i] = R() ^ h[i-1];
	for(; q; --q) W(h[R()-1] ^ h[R()]);
	fwrite(outbuf, 1, outp, stdout);
}