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

const int kN = 100001;

int n, m;
vector<int> adj[kN];

int pre[kN], low[kN], tot;
int ins[kN], scc[kN], cnt;
int head[kN];
vector<int> stk;
void tarjan(int u) {
	pre[u] = low[u] = ++tot;
	ins[u] = true; stk.pb(u);
	for (int &v: adj[u]) {
		if (pre[v] == 0) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (ins[v]) low[u] = min(low[u], pre[v]);
	}
	if (low[u] == pre[u]) {
		++cnt;
		int v;
		do {
			v = stk.back();
			stk.pop_back();
			ins[v] = false;
			scc[v] = cnt;
		} while (v != u);
		head[cnt] = u;
	}
}

vector<int> bdj[kN];
int outdeg[kN], indeg[kN];
int vis[kN];

int matched[kN];
vector<pii> match;
vector<int> needIn, needOut;

bool dfs(int u, int from) {
	vis[u] = true;
	if (outdeg[u] == 0) {
		if (matched[from]) vis[u] = false;
		else {
			matched[from] = true;
			match.pb(from, u);
		}
		return true;
	}
	int cnt = 0;
	for (int &v: bdj[u])
		if (!vis[v]) cnt += dfs(v, from);
	if (indeg[u] == 0 and cnt == 0) needIn.pb(u);
	return (cnt != 0);
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	cin >> n >> m;
	for (int u, v, i = 0; i < m; ++i) {
		cin >> u >> v;
		adj[u].pb(v);
	}

	for (int u = 1; u <= n; ++u)
		if (pre[u] == 0) tarjan(u);

	for (int i = 1; i <= n; ++i)
		for (int &j: adj[i]) {
			int u = scc[i], v = scc[j];
			if (u != v) {
				bdj[u].pb(v);
				++outdeg[u];
				++indeg[v];
			}
		}

	if (cnt == 1) {
		cout << 0 << '\n';
		return 0;
	}

	for (int i = 1; i <= n; ++i)
		debug(i, scc[i]);
	for (int i = 1; i <= cnt; ++i)
		debug(i, bdj[i]);

	for (int u = 1; u <= cnt; ++u)
		if (indeg[u] == 0) dfs(u, u);
	for (int u = 1; u <= cnt; ++u)
		if (!vis[u]) needOut.pb(u);

	debug(match);
	debug(needIn);
	debug(needOut);

	vector<pii> ans;
	while (!needIn.empty() and !needOut.empty()) {
		int u = needIn.back(); needIn.pop_back();
		int v = needOut.back(); needOut.pop_back();
		ans.pb(v, u);
	}

	for (int i = 0; i + 1 < match.size(); ++i)
		ans.pb(match[i].ss, match[i+1].ff);

	int lst = match.back().ss;
	while (!needIn.empty()) {
		ans.pb(lst, needIn.back());
		lst = needIn.back();
		needIn.pop_back();
	}
	while (!needOut.empty()) {
		ans.pb(lst, needOut.back());
		lst = needOut.back();
		needOut.pop_back();
	}
	ans.pb(lst, match[0].ff);

	cout << ans.size() << '\n';
	for (auto &[u, v]: ans)
		cout << head[u] << ' ' << head[v] << '\n';

	return 0;
}
