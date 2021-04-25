#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = ' '; return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = ' ';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

const int N = 1e4;
int n, a[N], stop;
short l, r, m;
int mn;
struct jizz{
	short l, r;
	jizz(){}
	jizz(int l, int r): l(l), r(r){}
} stck[N];

int main(){
	while((n = R()) != 0){
		FOR(i, n) a[i] = R();
		stop = 0;
		stck[stop++] = {0, (short)n};
		while(stop > 0){
			--stop, l = stck[stop].l, r = stck[stop].r;
			if(l == r) continue;
			if(l == r - 1){ W(a[l]); continue;}
			m = l, mn = a[l];
			for(short i = l; i < r; ++i)
				if(a[i] < mn) m = i, mn = a[i];
			W(mn);
			stck[stop++] = {m + 1, r};
			stck[stop++] = {l, m};
		}
		outbuf[outp++] = '\n';
	}
	fwrite(outbuf, 1, outp, stdout);
}