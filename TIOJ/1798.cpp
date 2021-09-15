// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
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
#define debug(...) ((void)0)
#endif

const int kN = 1000001;

int N, M, K, Q;
int he[kN], to[kN*2], pr[kN*2];
int dep[kN], par[kN];
int f[kN];

int F(int a){ return a == f[a] ? a : f[a] = F(f[a]); }

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M >> K >> Q;
	for(int i = 1; i <= N; ++i) he[i] = -1;
	for(int i = 1; i <= N; ++i) f[i] = i;
	for(int u, v, i = 0, j = 0; i < M; ++i){
		cin >> u >> v;
		to[j] = v; pr[j] = he[u]; he[u] = j++;
		to[j] = u; pr[j] = he[v]; he[v] = j++;
	}
	queue<int> q; q.push(1);
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int e = he[u]; e != -1; e = pr[e]){
			int v = to[e];
			if(v == par[u]) continue;
			par[v] = u;
			dep[v] = dep[u] + 1;
			q.push(v);
		}
	}
	for(int u, v, i = 0; i < K; ++i){
		cin >> u >> v;
		while(u != v){
			if(dep[u] < dep[v]) swap(u, v);
			f[u] = par[u];
			u = F(u);
		}
	}
	for(int i = 1; i <= N; ++i) F(i);
	for(int u, v, i = 0; i < Q; ++i){
		cin >> u >> v;
		cout << (f[u] == f[v]) << '\n';
	}
	return 0;
}
