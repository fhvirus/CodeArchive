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

const int kN = 3003;
const int kM = 6006;
int N, M, X, p[kN];
struct DIS {
	int d, k; vector<int> c;
	void get(){
		cin >> d >> k;
		c.resize(k);
		for(int i = 0; i < k; ++i)
			cin >> c[i];
	}
} dis[kM];

int f[kM];
void init(){ for(int i = 1; i <= M; ++i) f[i] = i; }
int F(int a){ return a == f[a] ? a : f[a] = F(f[a]); }
bool onion(int a, int b){
	a = F(a); b = F(b);
	if(a == b) return false;
	f[b] = a;
	return true;
}

pii has[kN];
vector<int> con[kM];
vector<int> sol;
vector<int> one[kM];
vector<int> two[kM];
void find_conflicts(){
	for(int i = 1; i <= M; ++i){
		for(int u: dis[i].c){
			auto &[a, b] = has[u];
			if(a == 0) a = i;
			else b = i;
		}
	}
	for(int i = 1; i <= N; ++i){
		auto [u, v] = has[i];
		if(u == 0 and v == 0) sol.pb(i);
		else if (v == 0) one[u].pb(i);
		else{ con[u].pb(v); con[v].pb(u); }
	}
	for(int i = 1; i <= M; ++i){
		auto &v = con[i];
		sort(AI(v)); v.erase(unique(AI(v)), end(v));
	}
}
void get_item_on_edge(){
	vector<int> dep(M+1, 0);
	queue<int> q;
	for(int i = 1; i <= M; ++i){
		if(dep[i]) continue;
		q.push(i); dep[i] = 1;
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(int v: con[u]){
				if(dep[v] != 0) continue;
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
	}
	for(int i = 1; i <= N; ++i){
		auto [u, v] = has[i];
		if(u == 0 or v == 0) continue;
		two[(dep[u] > dep[v] ? u : v)].pb(i);
	}
}

void mer(vector<int> &dp, vector<int> &sc){
	int n = dp.size()-1, m = sc.size()-1, sz = n+m+1;
	dp.resize(sz, X+1);
	for(int i = n; i >= 0; --i){
		for(int j = 1; j <= m; ++j)
			chmin(dp[i+j], dp[i]+sc[j]);
	}
	while(dp.back() > X) dp.pop_back();
}
void mer(vector<int> &dp, vector<int> &sc0, vector<int> &sc1){
	int n = dp.size()-1, m = sc0.size()-1, k = sc1.size()-1;
	dp.resize(n+max(m,k)+1, X+1);
	for(int i = n; i >= 0; --i){
		for(int j = 1; j <= m; ++j)
			chmin(dp[i+j], dp[i]+sc0[j]);
		for(int j = 1; j <= k; ++j)
			chmin(dp[i+j], dp[i]+sc1[j]);
	}
	while(dp.back() > X) dp.pop_back();
}
void put(vector<int> &dp, int v){
	int n = dp.size()-1;
	dp.pb(X+1);
	for(int i = n; i >= 0;  --i)
		chmin(dp[i+1], dp[i]+v);
	if(dp.back() > X) dp.pop_back();
}

bool vis[kM];
pair<vector<int>, vector<int>> dfs(int u){
	vis[u] = true;
	vector<int> dp0(1, 0), dp1(dis[u].k+1, X+1);
	dp1[0] = 0; dp1[dis[u].k] = dis[u].d;
	for(int v: con[u]){
		if(vis[v]) continue;
		auto [sc0, sc1] = dfs(v);
		mer(dp1, sc0);
		for(int i: two[v]) put(sc0, p[i]);
		mer(dp0, sc0, sc1);
	}
	for(int i: one[u]) put(dp0, p[i]);
	return {dp0, dp1};
}
void solve(){
	vector<int> dp(1, 0);
	for(int i = 1; i <= M; ++i){
		if(vis[i]) continue;
		auto [sc0, sc1] = dfs(i);
		mer(dp, sc0, sc1);
	}
	for(int i: sol) put(dp, p[i]);
	cout << dp.size()-1 << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M >> X;
	for(int i = 1; i <= N; ++i) cin >> p[i];
	for(int i = 1; i <= M; ++i) dis[i].get();

	if(M != 0){
		find_conflicts();
		get_item_on_edge();
	}
	solve();
	
	return 0;
}
