#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
constexpr int MAXN = 2e5 + 1;
constexpr int MAXL = 19;
constexpr int INF  = 8e7;

vector<int> adj[MAXN];
int depth[MAXN], siz[MAXN];
int anc[MAXL][MAXN];
int ans[MAXN];
// 記錄重心樹的父節點
int par[MAXN];

/*		dist	*/
int dfs(int u, int p, int d){
	depth[u] = d;
	anc[0][u] = p;
	int s = 1;
	for(int v: adj[u]){
		if(v != p)
			s += dfs(v, u, d+1);
	}
	return siz[u] = s;
}
void initLCA(int n){
	for(int j = 1; j < MAXL; j++){
		for(int i = 1; i <= n; i++)
			anc[j][i] = anc[j-1][anc[j-1][i]];
	}
}
int LCA(int a, int b){
	if(depth[a] < depth[b]) swap(a, b);
	int d = depth[a] - depth[b];
	for(int i = MAXL-1; i >= 0; --i){
		if((1 << i) & d) a = anc[i][a];
	}
	if(a == b) return a;
	for(int i = MAXL-1; i >= 0; --i){
		if(anc[i][a] != anc[i][b]){
			a = anc[i][a];
			b = anc[i][b];
		}
	}
	return anc[0][a];
}
int dist(int a, int b){
	return depth[a] + depth[b] - (depth[LCA(a, b)] << 1);
}

/*	centroid decomposition	*/
// 拔掉點之後的大小
bool vis[MAXN];
int getSize(int u, int p){
	int s = 1;
	for(int v: adj[u]){
		if(!vis[v] and v != p)
			s += getSize(v, u);
	}
	// 因為 child size 只會在心剖分的時候用到一次
	// 所以直接存起來即可
	// 有一點啟發式合併的 fu
	return siz[u] = s;
}
int getCentroid(int u, int p, int n){
	for(int v: adj[u]){
		if(v != p and !vis[v] and (siz[v] << 1) > n)
			return getCentroid(v, u, n);
	}
	return u;
}
int centroidDecomposition(int u, int p){
	getSize(u, p);
	int c = getCentroid(u, p, siz[u]);
	// 拔掉點
	vis[c] = true;
	for(int i: adj[c]){
		// 因為上兩行一定會把父節點標上
		// 所以只要判 vis[i]
		if(!vis[i]){
			par[centroidDecomposition(i, c)] = c;
		}
	}
	return c;
}

/*	modify & query	*/
void modify(int a){
	int now = a;
	while(now != 0){
		ans[now] = min(ans[now], dist(a, now));
		now = par[now];
	}
}

int query(int a){
	int res = ans[a], now = a;
	while(now != 0){
		res = min(res, ans[now] + dist(a, now));
		now = par[now];
	}
	return res;
}

void init(int n){
	dfs(1, 0, 1);
	initLCA(n);
	centroidDecomposition(1, 0);

	memset(vis, false, sizeof(vis));
	memset(ans, 127, sizeof(ans));
	modify(1);
}

int main(){OW0
	int n, m;
	cin >> n >> m;
	for(int i = 1, a, b; i < n; i++){
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	init(n);

	for(int cmd, a; m; --m){
		cin >> cmd >> a;
		if(cmd == 1){
			modify(a);
		} else {
			cout << query(a) << '\n';
		}
	}
	return 0;
}