#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
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

#define N 100001
int n, m;
int head[N], to[N<<1], prv[N<<1];

// Heavy light decomposition
int par[18][N], dep[N];
void dfs(int u){
	for(int v = head[u]; v != -1; v = prv[v]){
		if(dep[to[v]]) continue;
		dep[to[v]] = dep[u] + 1;
		par[0][to[v]] = u;
		dfs(to[v]);
	}
}
inline void initLCA(){
	for(int i = 1; i < 18; ++i)
		for(int j = 0; j < n; ++j)
			par[i][j] = par[i-1][par[i-1][j]];
}
inline int lca(int u, int v){
	if(dep[u] < dep[v]) u ^= v, v ^= u, u ^= v;
	int d = dep[u] - dep[v];
	// printf("LCA: %d %d %d\n",u, v, d);
	for(int i = 17; i >= 0; --i)
		if((1<<i) & d) u = par[i][u];
	// printf("EEK: %d %d\n", u, v);
	if(u == v) return u;
	for(int i = 17; i >= 0; --i)
		if(par[i][u] != par[i][v])
			u = par[i][u],
			v = par[i][v];
	return par[0][u];
}

int main(){
	n = R(), m = R();
	for(int i = 0; i < n; ++i) head[i] = -1;
	for(int a, b, i = 1, j = 0; i < n; ++i){
		a = R(), b = R();
		to[j] = b, prv[j] = head[a], head[a] = j++;
		to[j] = a, prv[j] = head[b], head[b] = j++;
	}
	dep[0] = 1;
	dfs(0);
	initLCA();
	for(int a, b, l, i = 0; i < m; ++i){
		a = R(), b = R();
		l = lca(a, b);
		W(dep[a] + dep[b] - 2 * dep[l]);
	}
	fwrite(outbuf, 1, outp, stdout);
}