// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<vector>
#define pb push_back
using namespace std;
const int N = 10005;
int t, n, m;
vector<int> adj[N], rdj[N], sccadj[N];
bool vis[N];
vector<int> stk;
int scc[N], sccsz[N], ans[N];

void dfs(int u){
	vis[u] = true;
	for(int v: adj[u]){
		if(vis[v]) continue;
		dfs(v);
	}
	stk.pb(u);
}
int dfs2(int u){
	vis[u] = true;
	int ans = 1;
	for(int v: rdj[u]){
		if(vis[v]) continue;
		scc[v] = scc[u];
		dfs2(v);
	}
	return ans;
}
void dds(int u){
	int eek = 0;
	for(int v: sccadj[u]){
		if(ans[v]) eek = max(eek, ans[v]);
		else{
			dds(v);
			eek = max(eek, ans[v]);
		}
	}
	ans[u] = eek + sccsz[u];
}
void solve(){
	n = R(), m = R();
	for(int i = 1; i <= n; ++i) adj[i].clear(), rdj[i].clear(), sccadj[i].clear();
	for(int i = 0, u, v; i < m; ++i){
		u = R(), v = R();
		adj[u].pb(v);
		rdj[v].pb(u);
	}
	fill(vis, vis + n + 1, false);
	stk.clear();
	for(int i = 1; i <= n; ++i)
		if(!vis[i]) dfs(i);

	fill(vis, vis + n + 1, false);
	for(int i = stk.size() - 1; i >= 0; --i){
		if(!vis[stk[i]]){
			scc[stk[i]] = stk[i];
			dfs2(stk[i]);
		}
	}
	for(int i = 1; i <= n; ++i){
		for(int j: adj[i])
			if(scc[i] != scc[j]) sccadj[scc[i]].pb(scc[j]);
	}
	
	fill(ans, ans + n + 1, 0);
	fill(sccsz, sccsz + n + 1, 0);
	for(int i = 1; i <= n; ++i)
		sccsz[scc[i]]++;

	int eek = 0;
	for(int i = 1; i <= n; ++i){
		if(scc[i] != i) continue;
		if(ans[i]) continue;
		dds(i);
		eek = max(eek, ans[i]);
	}
	W(eek);
}
int main(){
	for(t = R(); t; --t) solve();
	write(1,OB,OP);
	return 0;
}
