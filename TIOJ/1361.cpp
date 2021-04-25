#pragma Ofast
#pragma loop-opt(on)
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
#include<cstdio>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0'&&c!=EOF) c=readchar();
	if(c == EOF) return -1;
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
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}
int l, r;
const int pow10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
inline int jizz(int a){
	if(a < 0) return 0;
	int ans = 1;
	for(int i = 1; i < 10 and pow10[i] <= a; ++i){
		ans += (a / pow10[i]) * pow10[i-1];
		if(a % pow10[i] < pow10[i-1]) ans -= pow10[i-1] - a % pow10[i] - 1;
	}
	return ans;
}
int main(){
	while(l = R(), r = R(), l != -1){
		if(l > r) l ^= r, r ^= l, l ^= r;
		W(jizz(r) - jizz(l-1));
	}
	fwrite(outbuf, 1, outp, stdout);
	return 0;
}