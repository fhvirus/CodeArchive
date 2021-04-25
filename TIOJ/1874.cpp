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

int N = 1e7;
short anss[10000001];
int n, a, curmax = 1;
int main(){
	n = R();
	if(n <= 1000) N = 1000;
	for(int i = 1; i <= N; ++i) anss[i] = 1;
	for(; n; --n){
		a = R();
		if(curmax >= a){ W(anss[a]); continue;}
		for(++curmax; curmax <= a; ++curmax){
			if(anss[curmax] == 1){
				for(int j = 1; curmax * j <= N; ++j){
					int cnt = 2, p = curmax;
					while(j % p == 0) p *= curmax, ++cnt;
					anss[curmax * j] *= cnt;
				}
			}
		}
		--curmax;
		W(anss[a]);
	}
	fwrite(outbuf, 1, outp, stdout);
}