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

struct DS {
	int mnv, mxv;
	vector<int> cnt;
	DS () : mnv(0), mxv(-1), cnt(0) {}
	void insert(int v) {
		chmin(mnv, v);
		if(chmax(mxv, v)) cnt.resize(mxv+1, 0);
		++cnt[v];
	}
	void add1(int v) {
		assert(cnt[v] > 0);
		--cnt[v];
		if(v == mnv and cnt[v] == 0) ++mnv;
		insert(v+1);
	}
	void de(){
		debug(mnv, mxv, cnt);
	}
};
void merge(DS &a, DS &b) {
	if(a.mxv < b.mxv) swap(a, b);
	for(int i = b.mnv; i <= b.mxv; ++i)
		for(int j = 0; j < b.cnt[i]; ++j)
			a.insert(i);
	b.cnt.clear();
}

const int kN = 5005;
int N, M;
vector<int> adj[kN];

int deg[kN];
unordered_set<int> bkt[kN];
int ord[kN], tot;

int fa[kN], sz[kN];
DS  ds[kN];
int Find(int u) { return u == fa[u] ? u : fa[u] = Find(fa[u]); }
void Union(int u, int v){
	u = Find(u); v = Find(v);
	if(u == v) return;
	fa[v] = u;
	sz[u] += sz[v];
	merge(ds[u], ds[v]);
}

bool alive[kN];

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	// input
	cin >> N >> M;
	for(int u, v, i = 0; i < M; ++i){
		cin >> u >> v;
		adj[u].pb(v); ++deg[u];
		adj[v].pb(u); ++deg[v];
	}

	// decide order of remove
	int mnd = kN;
	for(int i = 1; i <= N; ++i) chmin(mnd, deg[i]);
	for(int i = 1; i <= N; ++i) bkt[deg[i]].insert(i);
	for(int k = 0; k < N; ++k){
		while(mnd < N and bkt[mnd].empty()) ++mnd;
		if(mnd == N) break;

		int u = *begin(bkt[mnd]);
		ord[tot++] = u;
		bkt[mnd].erase(u);
		deg[u] = 0;
		for(int v: adj[u]){
			if(deg[v] == 0) continue;
			bkt[deg[v]].erase(v);
			--deg[v];
			if(deg[v] < mnd) --mnd;
			bkt[deg[v]].insert(v);
		}
	}

	assert(tot == N);
	reverse(ord, ord+tot);

	// add vertex back
	for(int i = 1; i <= N; ++i) fa[i] = i;
	for(int i = 1; i <= N; ++i) sz[i] = 1;
	for(int i = 1; i <= N; ++i) deg[i] = 0;

	int ans = 0;
	for(int i = 0; i < N; ++i) {
		int u = ord[i];
		int lst = -1;
		int cur = 0;
		for(int v: adj[u]){
			if(alive[v]){
				ds[Find(v)].add1(deg[v]);
				Union(u, v);
				++cur;
			}
			++deg[v];
		}
		ds[Find(u)].insert(cur);

		chmax(ans, ds[Find(u)].mnv * sz[Find(u)]);
		alive[u] = true;
	}

	cout << ans << '\n';
	return 0;
}
