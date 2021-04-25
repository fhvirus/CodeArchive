#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline long long RL(){static char c;long long a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
#include<algorithm>
using namespace std;

// #define int ll
typedef long long ll;
const int N = 1001, L = 10, M = 500000;
struct edge{
	int u, v;
	ll c;
} E[M], notmst[M];

int n, m, dsu[N], ncnt;

int head[N], prv[N<<1];
edge to[N<<1];

int dep[N], anc[L][N];
ll mxc[L][N];

// dsu
int Find(int a){
	return a == dsu[a] ? a : dsu[a] = Find(dsu[a]);
}
bool Union(int a, int b){
	a = Find(a), b = Find(b);
	if(a == b) return false;
	dsu[b] = a;
	return true;
}

// lca
void dfs(int u, int p){
	for(int i = head[u]; i != -1; i = prv[i])
		if(to[i].v != p){
			dep[to[i].v] = dep[u] + 1;
			anc[0][to[i].v] = u;
			mxc[0][to[i].v] = to[i].c;
			dfs(to[i].v, u);
		}
}
ll maxcost(int a, int b){
	if(dep[a] < dep[b]) swap(a, b);
	ll mx = 0;
	for(int d = dep[a] - dep[b], l = L-1; l >= 0; --l)
		if(d >> l & 1) mx = max(mx, mxc[l][a]), a = anc[l][a];
	if(a == b) return mx;
	for(int l = L-1; l >= 0; --l)
		if(anc[l][a] != anc[l][b]){
			mx = max(mx, mxc[l][a]);
			mx = max(mx, mxc[l][b]);
			a = anc[l][a];
			b = anc[l][b];
		}
	mx = max(mx, mxc[0][a]);
	mx = max(mx, mxc[0][b]);
	return mx;
}

signed main(){
	n = R(), m = R();
	for(int i = 1; i <= n; ++i)
		dsu[i] = i, head[i] = -1;
	for(int i = 0; i < m; ++i)
		E[i] = {R(), R(), RL()};
	sort(E, E + m, [](edge a, edge b){return a.c < b.c;});
	ll mst = 0, cnt = 0;
	for(int i = 0, j = 0; i < m; ++i){
		edge e = E[i];
		if(!Union(e.u, e.v)) notmst[ncnt++] = e;
		else{
			mst += e.c, ++cnt;

			to[j] = {0, e.v, e.c}; prv[j] = head[e.u]; head[e.u] = j++;
			to[j] = {0, e.u, e.c}; prv[j] = head[e.v]; head[e.v] = j++;
		}
	}

	if(cnt != n-1){ puts("-1 -1"); return 0;}
	if(ncnt == 0){ printf("%lld -1\n", mst); return 0;}

	dfs(1, 1);
	for(int i = 1; i < L; ++i)
		for(int j = 1; j <= n; ++j){
			anc[i][j] = anc[i-1][anc[i-1][j]];
			mxc[i][j] = max(mxc[i-1][j], mxc[i-1][anc[i-1][j]]);
		}

	ll cost = 1ll<<62;
	for(int i = 0; i < ncnt; ++i)
		cost = min(cost, notmst[i].c - maxcost(notmst[i].u, notmst[i].v));

	printf("%lld %lld\n", mst, mst + cost);
	return 0;
}