#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<unistd.h>
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;

#include<cmath>
inline void W(long double ld, int n){
	int d = roundl(ld * 1000);
	outbuf[outp++] = d / 1000 + '0';
	outbuf[outp++] = '.';
	outbuf[outp++] = d % 1000 / 100 + '0';
	outbuf[outp++] = d % 100 / 10 + '0';
	outbuf[outp++] = d % 10 + '0';
	outbuf[outp++] = 'E';
	outbuf[outp++] = '+';
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = '\n'; return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) write(1, outbuf, outp), outp = 0;
}

#include<cstdio>
int n;
int main(){
	while((n = R()) != 0){
		long double jizz = (lgammal(2 * n + 1) - lgammal(n + 2) - lgammal(n + 1)) / logl(10);
		n = floorl(jizz);
		W(powl(10, jizz-n), n);
	}
	write(1, outbuf, outp);
}