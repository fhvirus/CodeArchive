#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#pragma GCC target("avx,avx2")

#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
inline int max(int a, int b){ return a > b ? a : b;}
inline int min(int a, int b){ return a < b ? a : b;}


const int N = 1e6;
int n, m;
int head[N], to[N], prv[N];

int pre[N], t, low[N], scc[N];
int stk[N], top;
bool instack[N];
int scchead[N], sccto[N], sccprv[N], jiz;
int sccsz[N], sccin[N];

void tarjan(int u){
	low[u] = pre[u] = ++t;
	stk[top++] = u; instack[u] = true;
	for(int v = head[u]; v != -1; v = prv[v]){
		if(pre[to[v]] == 0)
			tarjan(to[v]), low[u] = min(low[u], low[to[v]]);
		else if(instack[to[v]])
			low[u] = min(low[u], pre[to[v]]);
	}
	if(low[u] == pre[u]){
		int v;
		do{
			v = stk[--top];
			instack[v] = false;
			scc[v] = u;
			++sccsz[u];
		} while(v != u);
	}
}

bool vis[N];
int eek[N];
void dfs(int u){
	vis[u] = true;
	int ans = 0;
	for(int v = scchead[u]; v != -1; v = sccprv[v]){
		if(!vis[sccto[v]])
			dfs(sccto[v]);
		ans = max(ans, eek[sccto[v]]);
	}
	eek[u] = ans + sccsz[u];
}

int main(){
	n = R(), m = R();
	for(int i = 0; i < n; ++i)
		head[i] = scchead[i] = -1;
	for(int i = 0, a, b; i < m; ++i){
		a = R(), b = R();
		to[i] = b, prv[i] = head[a], head[a] = i;
	}
	for(int i = 0; i < n; ++i)
		if(pre[i] == 0) tarjan(i);
	for(int u = 0; u < n; ++u)
		for(int v = head[u]; v != -1; v = prv[v])
			if(scc[u] != scc[to[v]])
				sccto[jiz] = scc[to[v]],
				sccprv[jiz] = scchead[scc[u]],
				scchead[scc[u]] = jiz++;

	int ans = 0;
	for(int i = 0; i < n; ++i)
		if(scc[i] == i and sccin[scc[i]] == 0){
			dfs(i), ans = max(ans, eek[i]);
		}

	printf("%d", ans);
	return 0;
}