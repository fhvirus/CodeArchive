#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
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

const int N = 1e6;
int n, m, color[N * 2 + 1], dsu[N], jizz[N], yike[N];

inline int findColor(int a){
	return color[a] == a ? a : color[a] = findColor(color[a]);
}
inline void unionColor(int a, int b){
	if(findColor(a) == findColor(b)) return;
	color[color[b]] = color[a];
}
inline int findSet(int a){
	return dsu[a] == a ? a : dsu[a] = findSet(dsu[a]);
}
inline void unionSet(int a, int b){
	if(findSet(a) == findSet(b)) return;
	dsu[dsu[b]] = dsu[a];
}

int main(){
	n = R(); m = R();
	for(int i = 1; i <= n; ++i)
		color[i] = i, dsu[i] = i, color[i + n] = i + n;
	for(int a, b; m; --m){
		a = R(), b = R();
		unionColor(a, b+n);
		unionColor(b, a+n);
		unionSet(a, b);
	}
	for(int i = 1; i <= n; i++)
		if(color[i] == color[i+n]){
			puts("-1");
			return 0;
		}
	int s=0, t=0;
	for(int i = 1; i <= n; ++i)
		if(findColor(i) == findColor(findSet(i))) jizz[s++] = i;
		else yike[t++] = i;
	W(s), W(t), outbuf[outp++] = '\n';

	FOR(i,s) W(jizz[i]);
	outbuf[outp++] = '\n';
	FOR(i,t) W(yike[i]);

	fwrite(outbuf, 1, outp, stdout);
	return 0;
}