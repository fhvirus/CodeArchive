#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")
#pragma loop_opt(on)
#include<unistd.h>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[20], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    write(1, outbuf, outp);
}

#include<algorithm>
const int N = 1e5+1;
int n, m, k, ans;
int dsu[N], jizz[N];
int Find(int a){ return a == dsu[a] ? a : dsu[a] = Find(dsu[a]);}
struct edge{
	int u, v, c;
} e[N];

int main(){
	n = R(), m = R();
	FOR(i, m) e[i] = {R(), R(), R()};
	std::sort(e, e + m, [](edge a, edge b){ return a.c > b.c;});
	k = R();
	for(; k; --k) jizz[R()] = true;
	FOR(i, n+1) dsu[i] = i;
	FOR(i, m){
		int a = Find(e[i].u), b = Find(e[i].v);
		if(a == b) continue;
		if(jizz[a] and jizz[b]) ans += e[i].c;
		else{
			dsu[a] = b;
			jizz[a] |= jizz[b];
			jizz[b] |= jizz[a];			
		}
	}
	W(ans);
}