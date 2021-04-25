#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#define N 100001
int n, m;
int head[N], to[N<<1], prv[N<<1];

// Heavy light decomposition
int par[N], dep[N], siz[N], son[N];
int top[N];
void dfs1(int u){
	son[u] = -1;
	siz[u] = 1;
	for(int v = head[u]; v != -1; v = prv[v]){
		if(dep[to[v]]) continue;
		dep[to[v]] = dep[u] + 1;
		par[to[v]] = u;
		dfs1(to[v]);
		siz[u] += siz[to[v]];
		if(son[u] == -1 or siz[to[v]] > siz[son[u]]) son[u] = to[v];
	}
}
void dfs2(int u, int t){
	top[u] = t;
	if(son[u] == -1) return;
	dfs2(son[u], t);
	for(int v = head[u]; v != -1; v = prv[v])
		if(to[v] != par[u] and to[v] != son[u])
			dfs2(to[v], to[v]);
}
inline int lca(int u, int v){
	while(top[u] != top[v]){
		if(dep[top[u]] > dep[top[v]])
			u = par[top[u]];
		else
			v = par[top[v]];
	}
	return dep[u] < dep[v] ? u : v;
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
	dfs1(0);
	dfs2(0, 0);
	for(int a, b, l, i = 0; i < m; ++i){
		a = R(), b = R();
		l = lca(a, b);
		W(dep[a] + dep[b] - 2 * dep[l]);
	}
	write(1,OB,OP);
}