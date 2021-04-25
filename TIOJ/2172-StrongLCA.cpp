#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

const int N = 100001;
int n, m;
int head[N], to[N<<1], prv[N<<1];

// Heavy light decomposition
int par[N], dep[N], tio[N];
void dfs(int u, int p = -1){
	if(p != -1){
		par[u] = p;
		dep[u] = dep[p] + 1;
		if(dep[tio[tio[p]]] - dep[tio[p]] ==
			dep[tio[p]] - dep[p])
			tio[u] = tio[tio[p]];
		else tio[u] = p;
	}
	for(int v = head[u]; v != -1; v = prv[v])
		if(to[v] != p) dfs(to[v], u);
}
int lca(int a, int b){
	if(dep[a] < dep[b]){ int t = a; a = b; b = t;}

	while(dep[a] > dep[b])
		if(dep[tio[a]] >= dep[b]) a = tio[a];
		else a = par[a];

	if(a == b) return a;

	while(par[a] != par[b])
		if(tio[a] != tio[b]){
			a = tio[a];
			b = tio[b];
		} else {
			a = par[a];
			b = par[b];
		}

	return par[a];
}

int main(){
	n = R(), m = R();
	for(int i = 0; i < n; ++i) head[i] = -1;
	for(int a, b, i = 1, j = 0; i < n; ++i){
		a = R(), b = R();
		to[j] = b, prv[j] = head[a], head[a] = j++;
		to[j] = a, prv[j] = head[b], head[b] = j++;
	}
	dfs(0);
	for(int a, b, l, i = 0; i < m; ++i){
		a = R(), b = R();
		l = lca(a, b);
		W(dep[a] + dep[b] - 2 * dep[l]);
	}
	write(1,OB,OP);
}