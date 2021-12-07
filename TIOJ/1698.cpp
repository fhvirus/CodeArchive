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

struct Edge {
	int a, b, c, i;
	Edge (int a, int b, int c, int i): a(a), b(b), c(c), i(i) {}
	bool operator < (const Edge &rhs) const { return c < rhs.c; }
};
struct DSU {
	int n; vector<int> f;
	DSU (int nn): n(nn), f(nn+1, 0) { iota(AI(f), 0); }
	int F(int u) { return u == f[u] ? u : f[u] = F(f[u]); }
	bool M(int u, int v) {
		u = F(u); v = F(v);
		if (u == v) return false;
		f[v] = u;
		--n;
		return true;
	}
	int operator() (int u) { return F(u); }
};

const int kN = 100001;
vector<pii> adj[kN];
int low[kN], pre[kN], tot;
vector<int> ans;

void dfs(int u, int p) {
	pre[u] = low[u] = ++tot;
	for (auto &[v, i]: adj[u]) {
		if (i == p) continue;
		if (pre[v] == 0) {
			dfs(v, i);
			low[u] = min(low[u], low[v]);
		} else low[u] = min(low[u], pre[v]);
	}
	if (low[u] == pre[u] and p != 0)
		ans.pb(p);
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	int N, M; cin >> N >> M;
	vector<Edge> edges;
	for (int a, b, c, i = 1; i <= M; ++i) {
		cin >> a >> b >> c;
		edges.pb(a, b, c, i);
	}
	sort(AI(edges));

	DSU dsu(N);
	for (int i = 0, j = 0; i < M; i = j) {
		while (edges[i].c == edges[j].c) ++j;
		vector<int> vs;
		for (int k = i; k < j; ++k) {
			auto [a, b, c, id] = edges[k];
			a = dsu(a); b = dsu(b);
			if (a == b) continue;
			adj[a].pb(b, id); vs.pb(a);
			adj[b].pb(a, id); vs.pb(b);
		}

		sort(AI(vs)); vs.erase(unique(AI(vs)), end(vs));
		for (int &u: vs) {
			if (pre[u] == 0)
				dfs(u, 0);
		}
		tot = 0;
		for (int &u: vs) {
			adj[u].clear();
			pre[u] = low[u] = 0;
		}

		for (int k = i; k < j; ++k) {
			auto [a, b, c, id] = edges[k];
			dsu.M(a, b);
		}
		if(dsu.n == 1) break;
	}

	sort(AI(ans));
	cout << ans.size() << '\n';
	for (int &i: ans)
		cout << i << ' ';
	cout << '\n';
	return 0;
}
