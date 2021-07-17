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

const int kN = 50005;
const int kL = 16;
const int kQ = 200002;
const int kP = 6;
const int kK = 60;

int wait[kP][kP + 1][kK];
constexpr void init(){
	for(int a = 0; a < kP; ++a)
		for(int p = 1; p <= kP; ++p)
			for(int t = 0; t < kK; ++t)
				wait[a][p][t] = (a - t + kK) % p;
}

int n, q;
vector<tuple<int, int, int, int, int>> adj[kN];

int an[kN][kL], dep[kN];
int up[kN][kL][kK];
int dw[kN][kL][kK];

void dfs(){
	an[1][0] = 1, dep[1] = 0;
	vector<int> stk; stk.pb(1);
	while(!stk.empty()){
		int u = stk.back(); stk.pop_back();
		for(auto [v, w, a, b, p]: adj[u]){
			if(v == an[u][0]) continue;
			an[v][0] = u, dep[v] = dep[u] + 1;
			for(int t = 0; t < kK; ++t) dw[v][0][t] = wait[a][p][t] + w;
			for(int t = 0; t < kK; ++t) up[v][0][t] = wait[b][p][t] + w;
			stk.pb(v);
		}
	}
}
constexpr void tr(int r[kK], int a[kK], int b[kK]){
	for(int t = 0; t < kK; ++t)
		r[t] = a[t] + b[(t + a[t]) % kK];
}
int lca(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	for(int d = dep[u] - dep[v], l = 0; d; d >>= 1, ++l)
		if(d & 1) u = an[u][l];
	if(u == v) return u;
	for(int l = kL - 1; l >= 0; --l)
		if(an[u][l] != an[v][l]){
			u = an[u][l];
			v = an[v][l];
		}
	return an[u][0];
}
int query(int u, int v, int t){
	int lc = lca(u, v);
	int du = dep[u] - dep[lc];
	int dv = dep[v] - dep[lc];
	int ans = 0;

	// u go up
	for(int l = 0; du; du >>= 1, ++l)
		if(du & 1){
			ans += up[u][l][t];
			t = (t + up[u][l][t]) % kK;
			u = an[u][l];
		}

	// v go dw
	vector<pii> go;
	for(int l = 0; dv; dv >>= 1, ++l)
		if(dv & 1){
			go.pb(v, l);
			v = an[v][l];
		}

	reverse(AI(go));
	for(auto [v, l]: go){
		ans += dw[v][l][t];
		t = (t + dw[v][l][t]) % kK;
	}

	return ans - 1;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	init();

	cin >> n >> q;
	for(int u, v, w, a, b, p, i = 1; i < n; ++i){
		cin >> u >> v >> w >> a >> b >> p; ++w;
		adj[u].pb(v, w, a, b, p);
		adj[v].pb(u, w, b, a, p);
	}

	dfs();

	for(int l = 1; l < kL; ++l){
		for(int i = 1; i <= n; ++i){
			an[i][l] = an[an[i][l-1]][l-1];
			tr(dw[i][l], dw[an[i][l-1]][l-1], dw[i][l-1]);
			tr(up[i][l], up[i][l-1], up[an[i][l-1]][l-1]);
		}
	}

	for(int h, m, s, t, i = 0; i < q; ++i){
		cin >> h >> m >> s >> t;
		cout << query(s, t, m) << '\n';
	}
	return 0;
}
