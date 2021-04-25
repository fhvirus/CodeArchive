#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}

const int N = 1e5+1, M = 3e5, INF = 1e9;
int n, m, k, mst, Mst;

int dsu[N], eek;
inline int Find(int a){ return a == dsu[a] ? a : dsu[a] = Find(dsu[a]);}

struct edge{
	int u, v;
} zero[M], one[M], e;
int z, o;

int main(){
	n = R(), m = R(), k = R();
	for(int i = 0, a, b, c; i < m; ++i){
		e = {R(), R()}, c = R();
		(c == 0 ? zero[z++] : one[o++]) = e; 
	}

	eek = n; for(int i = 1; i <= n; ++i) dsu[i] = i;
	for(int i = 0; i < o and eek > 1; ++i){
		if(Find(one[i].u) == Find(one[i].v)) continue;
		dsu[dsu[one[i].u]] = dsu[one[i].v], ++Mst;
	}
	// for(int i = 0; i < z and eek > 1; ++i){
	// 	if(Find(zero[i].u) == Find(zero[i].v)) continue;
	// 	dsu[dsu[zero[i].u]] = dsu[zero[i].v];
	// }

	if(Mst < k){ puts("NIE"); return 0;}
	if(Mst == k){ puts("TAK"); return 0;}

	eek = n; for(int i = 1; i <= n; ++i) dsu[i] = i;
	for(int i = 0; i < z and eek > 1; ++i){
		if(Find(zero[i].u) == Find(zero[i].v)) continue;
		dsu[dsu[zero[i].u]] = dsu[zero[i].v];
	}
	for(int i = 0; i < o and eek > 1; ++i){
		if(Find(one[i].u) == Find(one[i].v)) continue;
		dsu[dsu[one[i].u]] = dsu[one[i].v], ++mst;
	}
	// mst = n - eek;
	puts(mst <= k and k <= Mst ? "TAK" : "NIE");
}