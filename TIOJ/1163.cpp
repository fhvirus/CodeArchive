#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = '\n'; return;}
    if(n == -1){outbuf[outp++] = '-'; outbuf[outp++] = '1'; outbuf[outp++] = '\n'; return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

#include<algorithm>
using namespace std;

const int N = 30000 + 1, M = 50000;

struct edge{
	int u, v, c;
	bool operator<(const edge &rhs) const{
		return c < rhs.c;
	}
} E[M];
int n, m, q;
int head[N], prv[M<<1];
edge adj[M<<1];


// disjoint sets
int dsu[N];
inline int Find(int a){
	return a == dsu[a] ? a : dsu[a] = Find(dsu[a]);
}
inline void Union(int a, int b){
	(Find(a) != Find(b)) and (dsu[dsu[b]] = dsu[a]);
}

// lowest common ancestor
const int L = 16;
int depth[N], anc[L][N], mxc[L][N];
void dfs(int u, int d){
	edge e;
	for(int i = head[u]; i != -1; i = prv[i]){
		e = adj[i];
		if(depth[e.v] == 0)
			depth[e.v] = d + 1,
			anc[0][e.v] = u,
			mxc[0][e.v] = e.c,
			dfs(e.v, d + 1);
	}
}
inline void initLCA(){
	for(int i = 1; i < L; ++i)
		for(int j = 1; j <= n; ++j)
			anc[i][j] = anc[i-1][anc[i-1][j]],
			mxc[i][j] = max(mxc[i-1][j], mxc[i-1][anc[i-1][j]]);
}
inline int lca(int a, int b){
	if(depth[a] < depth[b]) swap(a, b);
	int d = depth[a] - depth[b], mx = 0;
	for(int i = L-1; i >= 0; --i)
		if((1<<i) & d)
			mx = max(mx, mxc[i][a]),
			a = anc[i][a];
	if(a == b) return mx;

	for(int i = L-1; i >= 0; --i)
		if(anc[i][a] != anc[i][b])
			mx = max(mx, mxc[i][a]),
			mx = max(mx, mxc[i][b]),
			a = anc[i][a],
			b = anc[i][b];

	mx = max(mx, mxc[0][a]);
	mx = max(mx, mxc[0][b]);
	return mx;
}

int main(){
	n = R(), m = R();
	for(int i = 1; i <= n; ++i)
		dsu[i] = i, head[i] = -1;
	for(int i = 0; i < m; ++i)
		E[i] = {R(), R(), R()};
	sort(E, E + m);

	for(int i = 0, jizz = 0; i < m; ++i)
		if(Find(E[i].u) != Find(E[i].v)){
			Union(E[i].u, E[i].v);
			adj[jizz] = {E[i].u, E[i].v, E[i].c},
			prv[jizz] = head[E[i].u], head[E[i].u] = jizz++;

			adj[jizz] = {E[i].v, E[i].u, E[i].c},
			prv[jizz] = head[E[i].v], head[E[i].v] = jizz++;
		}

	for(int i = 1; i <= n; ++i)
		if(depth[i] == 0)
			depth[i] = i,
			dfs(i, 1);
	initLCA();

	q = R();
	for(int a, b; q; --q){
		a = R(), b = R();
		W(a == b ? 0 : (Find(a) != Find(b) ? -1 : lca(a, b)));
	}

	fwrite(outbuf, 1, outp, stdout);
}