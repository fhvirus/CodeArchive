// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
#ifdef OWO
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
#else
#pragma GCC optimize("Ofast")
#define debug(...) ((void)0)
#endif

// Special thanks to Omelet
// source: https://blog.csdn.net/Jarily/article/details/8779621

const int kN = 2002;
const int inf = 1e9 + 7;
const ll INF = 1e18;

int N, K, C[kN];
pii pos[kN];

struct EDG {
	int to, we, pr, nx;
	EDG () {}
	EDG(int t, int w, int p, int n):
		to(t), we(w), pr(p), nx(n) {}
};
int he[kN], tot;
EDG adj[kN * 4];

int has[kN];

void init(){
	tot = 0;
	for(int i = 0; i <= N; ++i) he[i] = -1;
	for(int i = 0; i <= N; ++i) has[i] = 0;
}
void addEdge(int u, int v, int w){
	adj[tot] = EDG(v, w, he[u], -1); if(~he[u]) adj[he[u]].nx = tot; he[u] = tot++;
	adj[tot] = EDG(u, w, he[v], -1); if(~he[v]) adj[he[v]].nx = tot; he[v] = tot++;
}
void delEdge(int eid){
	auto &e = adj[eid];
	if(~e.nx) adj[e.nx].pr = e.pr;
	if(~e.pr) adj[e.pr].nx = e.nx;
	int u = adj[eid xor 1].to;
	if(eid == he[u]) he[u] = e.pr, e.nx = -1;
}

int vis[kN], dis[kN], par[kN];
inline int getDis(int u, int v){
	auto &[ux, uy] = pos[u];
	auto &[vx, vy] = pos[v];
	return (ux - vx) * (ux - vx) + (uy - vy) * (uy - vy);
}
inline void relax(int u){
	for(int v = 1; v <= N; ++v)
		if(!vis[v] and chmin(dis[v], getDis(u, v)))
			par[v] = u;
}
ll prim(){
	for(int i = 0; i <= N; ++i) vis[i] = 0;
	for(int i = 0; i <= N; ++i) dis[i] = inf;
	for(int i = 0; i <= N; ++i) par[i] = 0;

	ll ans = 0;
	vis[1] = true; relax(1);
	for(int k = 1; k < N; ++k){
		int mni = 0;
		for(int u = 1; u <= N; ++u)
			if(!vis[u] and dis[u] < dis[mni])
				mni = u;
		vis[mni] = true;
		ans += dis[mni];
		addEdge(mni, par[mni], dis[mni]);
		relax(mni);
	}
	return ans;
}

int mxe[kN];
void dfs(int u, int p, int e = -1){
	mxe[u] = e;
	for(int i = he[u]; ~i; i = adj[i].pr){
		auto &[to, we, pr, nx] = adj[i];
		if(to == p) continue;
		dfs(to, u, (e == -1 or we > adj[e].we ? i : e));
	}
}

void solve(){
	cin >> N >> K; K = min(K, N);
	for(int i = 1; i <= N; ++i)
		cin >> pos[i].ff >> pos[i].ss >> C[i];

	init();
	ll ans = prim(), tmp = ans;

	{
		int u = min_element(C + 1, C + N + 1) - C;
		addEdge(0, u, C[u]);
		tmp += C[u]; has[u] = true;
	}
	{
		for(int k = 2; k <= K; ++k){
			dfs(0, 0);
			int u = 0, mnv = inf;
			for(int i = 1; i <= N; ++i)
				if(!has[i] and mxe[i] != -1 and chmin(mnv, C[i] - adj[mxe[i]].we))
					u = i;
			if(mnv > 0) break;
			has[u] = true;
			delEdge(mxe[u]); delEdge(mxe[u] xor 1);
			addEdge(0, u, C[u]);
			tmp += mnv;
			ans = min(ans, tmp);
		}
	}

	cout << ans << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T; cin >> T;
	for(; T; --T) solve();
	return 0;
}
