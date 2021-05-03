// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll; typedef pair<int,int> pii;
#define pb emplace_back
const int N = 100001, L = 18;

int n, q;
vector<pii> adj[N];

int siz[N];
bool vis[N];
vector<int> com;

int dep[N];
int par[N];
ll dis[L][N];

int getSiz(int u, int p){
	siz[u] = 1; com.pb(u);
	for(auto [v, _]: adj[u])
		if(!vis[v] and v != p)
			siz[u] += getSiz(v, u);
	return siz[u];
}
int getCen(int u, int p, int s){
	for(auto [v, _]: adj[u])
		if(!vis[v] and v != p and siz[v] * 2 > s)
			return getCen(v, u, s);
	return u;
}
void getDis(int u, int d){
	vis[u] = true;
	for(auto [v, w]: adj[u])
		if(!vis[v]) dis[d][v] = dis[d][u] + w, getDis(v, d);
}
void cenDecomp(int u, int d, int p){
	getSiz(u, p);

	int cen = getCen(u, p, siz[u]);

	dis[d][cen] = 0;
	getDis(cen, d);
	for(int i: com) vis[i] = false;
	com.clear();

	vis[cen] = true;
	dep[cen] = d;
	par[cen] = p;

	for(auto [v, _]: adj[cen])
		if(!vis[v]) cenDecomp(v, d + 1, cen);
}

bool has[N];
int cnt[N];
ll sum[N];
void upd(int u){
	if(has[u]) return;
	has[u] = true;
	for(int d = dep[u], p = u; p != -1; p = par[p], --d){
		++cnt[p];
		sum[p] += dis[d][u] - dis[d-1][u];
	}
}
ll query(int u){
	ll ans = 0;
	int lsz = 0;
	for(int d = dep[u], p = u; p != -1; p = par[p], --d){
		ans += sum[p] + (cnt[p] - lsz) * dis[d][u];
		lsz = cnt[p];
	}
	return ans;
}

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> q;
	for(int u, v, w, i = 1; i < n; ++i){
		cin >> u >> v >> w;
		adj[u].pb(v, w);
		adj[v].pb(u, w);
	}

	cenDecomp(0, 1, -1);

	for(int t, x; q; --q){
		cin >> t >> x;
		if(t == 1) upd(x);
		else cout << query(x) << '\n';
	}
	return 0;
}
