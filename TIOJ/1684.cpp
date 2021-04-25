#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}
inline int min(int u, int v){ return u < v ? u : v;}

const int N = 1001, M = 1000001;
int n, m;
bool adj[N][N];

// Find Articulation Vertex
short pre[N], low[N], t, child;
short stck[N], top;
bool col[N], yas[N];

bool dfs(int u, bool c, bool isroot = false){
	bool odd = false, eek;
	pre[u] = low[u] = ++t;
	col[u] = c;
	stck[top++] = u;
	for(int v = 1; v <= n; ++v) if(adj[u][v]){
		++child;
		adj[u][v] = adj[v][u] = false;
		if(pre[v] == 0){
			eek = dfs(v, !c);
			low[u] = min(low[u], low[v]);
			if((!isroot and low[v] >= pre[u]) or (isroot and child > 1)){
				do{
					--top;
					if(eek) yas[stck[top]] = true;
				} while(stck[top] != v);
				if(eek) yas[u] = true;
			} else odd |= eek;
		} else {
			low[u] = min(low[u], pre[v]);
			if(col[u] == col[v]) odd = true;
		}
	}
	return odd;
}

int main(){
	while(n = R(), m = R(), n or m){
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n; ++j)
				adj[i][j] = true;
			adj[i][i] = false;
			low[i] = 0;
			pre[i] = 0;
			yas[i] = false;
		}
		for(int u, v; m; --m){
			u = R(), v = R();
			adj[u][v] = adj[v][u] = false;
		}

		t = 0;
		for(int i = 1; i <= n; ++i)
			if(pre[i] == 0){
				child = 0;
				bool curans = dfs(i, 0, true);
				while(top > 0) yas[stck[--top]] |= curans;
			}

		int ans = 0;
		for(int i = 1; i <= n; ++i)
			ans += !yas[i];
		W(ans);
	}
	write(1,OB,OP);
	return 0;
}