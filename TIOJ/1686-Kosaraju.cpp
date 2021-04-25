//Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
const int N = 2e4 + 225;
int n, m;
vector<int> adj[N], rdj[N];
bool vis[N];
int stk[N], top;
int scc[N], cnt;
int siz[N];

void dfs(int u){
	vis[u] = true;
	for(int v: adj[u]) if(!vis[v]) dfs(v);
	stk[top++] = u;
}
void sfd(int u){
	scc[u] = cnt, ++siz[cnt];
	for(int v: rdj[u]) if(!scc[v]) sfd(v);
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int a, b, s; m; --m){
		cin >> a >> b >> s;
		if(s == 0){
			adj[a].pb(b);
			adj[b + n].pb(a + n);
			rdj[b].pb(a);
			rdj[a + n].pb(b + n);
		} else {
			adj[a].pb(b + n);
			adj[b + n].pb(a);
			rdj[b + n].pb(a);
			rdj[a].pb(b + n);
		}
	}

	// Kosaraju
	FOO(i,1,2*n) if(!vis[i]) dfs(i); 
	OOF(i,top-1,0) if(!scc[stk[i]]) ++cnt, sfd(stk[i]);

	FOO(i,1,n) if(scc[i] == scc[i + n]) --siz[scc[i]];

	FOO(i,1,n) cout << siz[scc[i + n]] - 1 << '\n';
	return 0;
}
