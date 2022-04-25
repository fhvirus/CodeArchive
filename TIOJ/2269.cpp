// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
#ifdef OWO
#define debug(args...) SDF(#args,args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
#else
#define debug(...) ((void)0)
#endif

struct DSU {
	vector<int> f, s;
	DSU (int n = 0): f(n + 1), s(n + 1, 1) { iota(AI(f), 0); }
	int F(int u) { return u == f[u] ? u : f[u] = F(f[u]); }
	int operator () (int u) { return u == f[u] ? u : f[u] = F(f[u]); }
	bool M(int u, int v) {
		u = F(u); v = F(v);
		if (u == v) return false;
		f[v] = u;
		s[u] += s[v];
		return true;
	}
};

const int kN = 2002;
const int kM = 1000001;

int T, N, M, K;

struct Edge { int u, v, c; };
Edge es[kM];
bitset<kM> used;

DSU dsuq;
queue<int> eq;
void add_to_queue(int id) {
	if (used[id]) return;
	used[id] = true;
	if (!dsuq.M(es[id].u, es[id].v)) return;
	eq.push(id);
}

struct DS {
	DSU dsu;
	int par[kN], pe[kN], jmp[kN], dep[kN];
	vector<pii> adj[kN];
	int find_jump(int u) { return u == jmp[u] ? u : jmp[u] = find_jump(jmp[u]); }
	void init() {
		dsu = DSU(N);
		for (int i = 1; i <= N; ++i) {
			par[i] = i;
			pe[i] = -1;
			jmp[i] = i;
			dep[i] = 0;
			adj[i].clear();
		}
	}
	void rebuild(int o) {
		queue<int> q;
		q.push(o);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (const auto& [v, id]: adj[u]) {
				if (v == par[u]) continue;
				par[v] = u;
				pe[v] = id;
				jmp[v] = (used[id] ? jmp[u] : v);
				dep[v] = dep[u] + 1;
				q.push(v);
			}
		}
	}
	void add(int u, int v, int id) {
		int fu = dsu.F(u);
		int fv = dsu.F(v);
		if (fu == fv) {
			// remove edges;
			u = find_jump(u);
			v = find_jump(v);
			while (u != v) {
				debug(u, v);
				if (dep[u] < dep[v]) swap(u, v);
				assert(pe[u] != -1);
				add_to_queue(pe[u]);
				u = jmp[u] = find_jump(par[u]);
			}
			add_to_queue(id);
		} else {
			if (dsu.s[fu] < dsu.s[fv]) {
				swap(u, v);
				swap(fu, fv);
			}
			par[v] = u;
			pe[v] = id;
			jmp[v] = (used[id] ? jmp[u] : v);
			dep[v] = dep[u] + 1;
			// dfs and reroot v;
			rebuild(v);
			adj[u].pb(v, id);
			adj[v].pb(u, id);
			dsu.M(u, v);
		}
	}
} ds[kN];

void solve() {
	cin >> N >> M >> K;

	used.reset();
	dsuq = DSU(N);
	for (int i = 1; i <= K; ++i)
		ds[i].init();

	for (int u, v, c, i = 0; i < M; ++i) {
		cin >> u >> v >> c;
		debug(u, v, c);
		es[i] = {u, v, c};
		ds[c].add(u, v, i);
		while (!eq.empty()) {
			int e = eq.front(); eq.pop();
			for (int cc = 1; cc <= K; ++cc) {
				if (cc == es[e].c) continue;
				ds[cc].add(es[e].u, es[e].v, e);
			}
		}
	}

	cout << (used.count() == M ? "Yes\n" : "No\n");
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> T;

	while (T --> 0)
		solve();
	
	return 0;
}
// Knapsack DP is NP-Hard, but FFT is O(N log N).

