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

const int kN = 606, INF = 1e9 + 7;

int n, m1, m2, ans;
bool g[kN][kN];
int adj[kN][kN];

int pre[kN], low[kN], tot;
int stk[kN], ins[kN], top;

void tarjan(int u){
	pre[u] = low[u] = ++tot;
	stk[top++] = u, ins[u] = 1;
	for(int v = 1; v <= n; ++v){
		if(!g[u][v]) continue;
		if(pre[v] == 0){
			tarjan(v);
			chmin(low[u], low[v]);
		} else if(ins[v]) chmin(low[u], pre[v]);
	}

	if(low[u] == pre[u]){
		int v;
		vector<int> scc;
		do{
			v = stk[--top];
			ins[v] = false;
			scc.pb(v);
		} while(v != u);

		int tmp = 0;
		for(int i: scc) for(int j: scc) chmax(tmp, adj[i][j]);
		ans += tmp + 1;
	}
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m1 >> m2;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			adj[i][j] = (i != j ? INF : 0);

	for(int u, v, i = 0; i < m1; ++i){
		cin >> u >> v;
		g[u][v] = g[v][u] = true;
		chmin(adj[u][v], 1);
		chmin(adj[v][u], -1);
	}
	for(int u, v, i = 0; i < m2; ++i){
		cin >> u >> v;
		g[u][v] = true;
		chmin(adj[v][u], 0);
	}

	for(int k = 1; k <= n; ++k)
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j) chmin(adj[i][j], adj[i][k] + adj[k][j]);

	for(int i = 1; i <= n; ++i)
		if(adj[i][i] < 0){
			puts("NIE");
			return 0;
		}

	for(int i = 1; i <= n; ++i)
		if(pre[i] == 0) tarjan(i);

	cout << ans;

	return 0;
}
