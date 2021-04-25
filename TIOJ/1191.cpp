#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<unistd.h>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<10;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
char s[20], sptr;
inline int R(){
	while((s[0] = readchar()) < '0');
	sptr = 1;
	while((s[sptr++] = readchar()) >= '0');
	return sptr;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(long long n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) write(1, outbuf, outp), outp = 0;
}
long long ans;
int main(){
	while(R() and s[0] != '0'){
		ans = 0;
		for(int i = 0; s[i] >= '0'; ++i){
			if(s[i] > '6') --s[i];
			ans = ans * 9 + s[i] - '0';
		}
		W(ans);
	}
	write(1, outbuf, outp);
}