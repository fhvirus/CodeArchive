#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<algorithm>
#define FOR(i,n) for(int i=0;i<n;++i)
typedef unsigned uint;
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline uint R(){
	uint ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = '\n'; return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

constexpr int MAXN = 1e5;
constexpr int MAXL = 18;

uint maxval[MAXL][MAXN], minval[MAXL][MAXN];

int n, m, l, r, hb;

int main(){
	n = R(), m = R();
	FOR(i,n) maxval[0][i] = minval[0][i] = R();
	for(uint j = 1; j < MAXL; j++)
		for(uint i = 0; i + (1 << j) - 1 < n; i++)
			minval[j][i] = std::min(minval[j-1][i], minval[j-1][i + (1 << (j-1))]),
			maxval[j][i] = std::max(maxval[j-1][i], maxval[j-1][i + (1 << (j-1))]);


	for(; m; --m){
		l = R()-1, r = R()-1, hb = 31 - __builtin_clz(r - l + 1);
		W(
			std::max(maxval[hb][l], maxval[hb][r - (1 << hb) + 1]) -
			std::min(minval[hb][l], minval[hb][r - (1 << hb) + 1])
		);
	}
	fwrite(outbuf, 1, outp, stdout);
	return 0;
}