#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

const int N = 1e6, L = 21;
int n, l, r, d, m[L][N];

inline int min(int a, int b){
	return a < b ? a : b;
}
int main(){
	n = R();
	FOR(i, n) m[0][i] = R();
	for(int i = 1; i < L; ++i)
		for(int j = 0; j + (1<<i) - 1< n; ++j)
			m[i][j] = min(m[i-1][j], m[i-1][j + (1<<(i-1))]);
	for(; n; --n)
		l = R()-1, r = R()-1, d = 31 - __builtin_clz(r - l + 1),
		W(min(m[d][l], m[d][r - (1<<d) + 1]) + 1);
	fwrite(outbuf, 1, outp, stdout);
}