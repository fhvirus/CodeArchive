#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline int min(int a, int b){
	return a < b ? a : b;
}
#include<vector>
using namespace std;
const int N = 300001;
int n, k, h[N];
vector<int> adj[N];

int pre[N], id, low[N], scc[N];
int S[N], p;
bool inStack[N];
void tarjan(int u){
	low[u] = pre[u] = ++id;
	S[p++] = u, inStack[u] = true;
	for(int v: adj[u]){
		if(pre[v] == 0){
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(inStack[v])
			low[u] = min(low[u], pre[v]);
	}
	if(low[u] == pre[u]){
		int v;
		do{
			v = S[--p];
			inStack[v] = false;
			scc[v] = u;
		} while(v != u);
	}
}

int sccsz[N], subsize[N];
vector<int> sccadj[N];
int dfs(int u){
	if(subsize[u] != 0) return subsize[u];
	subsize[u] = sccsz[u];
	int ans = 0;
	for(int v: sccadj[u]){
		ans = max(ans, dfs(v));
	}
	return subsize[u] += ans;
}

int main(){
	n = R(); k = R();
	for(int i = 1; i <= n; ++i) h[i] = R();
	adj[0].push_back(1);
	for(int i = 2; i <= n; ++i){
		if(h[i-1] <= h[i]) adj[i].push_back(i-1);
		if(h[i] <= h[i-1]) adj[i-1].push_back(i);
		adj[0].push_back(i);
	}

	char c;
	while(c != '.' and c != 'T') c = readchar();
	for(int i = 1; i <= n; ++i){
		if(c == 'T') adj[i].push_back(0);
		c = readchar();
	}

	for(int i = 1; i <= n; ++i)
		if(pre[i] == 0) tarjan(i);

	for(int i = 1; i <= n; ++i) ++sccsz[scc[i]];

	for(int i = 0; i <= n; ++i)
		for(int j: adj[i])
			if(scc[i] != scc[j])
				sccadj[scc[i]].push_back(scc[j]);

	printf("%d", dfs(scc[k]));
	return 0;
}