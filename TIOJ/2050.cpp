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

const int kN = 2002;

struct DSU {
	int n; vector<int> f;
	DSU(int n): n(n), f(n+1){
		iota(AI(f), 0);
	}
	int F(int a){ return a == f[a] ? a : f[a] = F(f[a]); }
	bool M(int a, int b){
		a = F(a); b = F(b);
		if(a == b) return false;
		f[b] = a;
		return true;
	}
};

vector<vector<int>> adj;
vector<int> pre, low;
int tot;
void tarjan(int u, int p, int e, vector<int> &isAP){
	pre[u] = low[u] = ++tot;
	int ch = 0;
	for(int v: adj[u]){
		if(v == p or v == e) continue;
		if(pre[v] == 0){
			++ch;
			tarjan(v, u, e, isAP);
			low[u] = min(low[u], low[v]);
			if(low[v] >= pre[u])
				isAP[u] = 1;
		} else if(pre[v] < pre[u])
			low[u] = min(low[u], pre[v]);
	}
	if(u == p and ch == 1)
		isAP[u] = 0;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N, M; cin >> N >> M;
	vector<DSU> spanningTrees(3, DSU(N));
	vector<pii> edges;
	adj.resize(N+1);
	for(int u, v, i = 0; i < M; ++i){
		cin >> u >> v;
		for(DSU &dsu: spanningTrees)
			if(dsu.M(u, v)){
				edges.pb(u, v);
				break;
			}
	}
	
	for(auto [u, v]: edges){
		adj[u].pb(v);
		adj[v].pb(u);
	}

	int ans = 0;
	vector<int> isAP(N+1, 0);

	pre.assign(N+1, 0);
	low.assign(N+1, 0);
	tot = 0;
	tarjan(1, 1, 0, isAP);

	for(int i = 1; i < N; ++i){
		fill(AI(pre), 0);
		fill(AI(low), 0);
		tot = 0;

		vector<int> tmp(N+1, 0);
		int cp = 0, lone = 0;
		for(int v: adj[i]){
			if(pre[v] != 0) continue;
			++cp; lone += ((int) adj[v].size() == 1 and v > i);
			tarjan(v, v, i, tmp);
		}
		if(isAP[i]) ans += N - i - ((cp == 2) ? lone : 0);
		else {
			for(int j = i+1; j <= N; ++j)
				if(tmp[j] == 1) ++ans;
		}
	}
	cout << ans << '\n';
	return 0;
}
