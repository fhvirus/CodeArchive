// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define OOF(i,a,b) for(int i=(a);i>=int(b);--i)
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
inline ll cdiv(ll x,ll m){return x/m+(x%m?(x<0)^(m>0):0);}
#ifdef OWO
#define safe cerr<<"\033[1;32m"<<__PRETTY_FUNCTION__<<" - "<<__LINE__<<" JIZZ\033[0m\n"
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
#else
#pragma GCC optimize("Ofast")
#define safe ((void)0)
#define debug(...) ((void)0)
#endif
const ll inf = 1e9, INF = 4e18;
const int N = 5e5 + 225, M = 1e9 + 7;
int n, m;
vector<int> adj[N];
int atm[N];
int s, p;
bool isb[N];

int pre[N], low[N], tot;
int stk[N], top;
bool ins[N];
int scc[N], cnt;
int sum[N];
bool has[N];

void tarjan(int u){
	low[u] = pre[u] = ++tot;
	stk[top++] = u; ins[u] = true;
	for(int v: adj[u]){
		if(!pre[v]){
			tarjan(v);
			chmin(low[u], low[v]);
		} else if(ins[v])
			chmin(low[u], pre[v]);
	}
	if(low[u] == pre[u]){
		int v;
		++cnt;
		do{
			v = stk[--top];
			sum[cnt] += atm[v];
			has[cnt] |= isb[v];
			ins[v] = false;
			scc[v] = cnt;
		} while(v != u);
	}
}

vector<vector<int>> dad;

void makedag(){
	for(int i = 1; i <= n; ++i)
		if(!pre[i]) tarjan(i);

	debug(vector<int>(scc, scc + n + 1));
	debug(vector<int>(has, has + n + 1));
	debug(vector<int>(sum, sum + n + 1));

	dad.resize(cnt + 1, vector<int>());
	for(int u = 1; u <= n; ++u)
		for(int v: adj[u])
			if(scc[u] != scc[v]) dad[scc[u]].pb(scc[v]);

	debug(dad);

	for(int i = 1; i <= cnt; ++i){
		sort(AI(dad[i]));
		dad[i].erase(unique(AI(dad[i])), end(dad[i]));
	}
}

bool hasdp[N];
int dp[N];

void dps(int u){
	if(hasdp[u]) return;
	hasdp[u] = true;
	int ans = 0;
	for(int v: dad[u]){
		dps(v);
		chmax(ans, dp[v]);
	}
	if(ans) dp[u] = ans + sum[u];
	else if(has[u]) dp[u] = sum[u];
	else dp[u] = 0;
	debug(u, ans, sum[u], dp[u]);
}

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int u, v; m; --m){
		cin >> u >> v;
		adj[u].pb(v);
	}
	for(int i = 1; i <= n; ++i)
		cin >> atm[i];
	cin >> s >> p;
	for(int u; p; --p){
		cin >> u;
		isb[u] = true;
	}

	makedag();

	dps(scc[s]);
	cout << dp[scc[s]];

	return 0;
}
