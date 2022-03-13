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

// consider doing reverse
// pluck the biggest and reachable out
// then update the neighbor to touched and reachable
// priority queue maintain valid points
// reach: can be reached from outside
// touch: has a neighbor plucked

struct DSU {
	int n, s; vector<int> f;
	DSU(int n = 0) : n(n), s(n), f(n+1) { iota(AI(f), 0); }
	int F(int a){ return a == f[a] ? a : f[a] = F(f[a]); }
	int M(int a, int b){
		a = F(a), b = F(b);
		if(a == b) return false;
		f[b] = a; --s; return true;
	}
	int operator() (int a){ return F(a); }
};
struct LISAN : vector<int> {
	void done() { sort(AI()); erase(unique(AI()), end()); }
	int operator() (int a) { return lower_bound(AI(), a) - begin(); }
};

const int kN = 150051;
const int INF = 1e9 + 7;

const array<pii, 4> d4 = {pii(1, 0), pii(-1, 0), pii(0, 1), pii(0, -1)};
const array<pii, 8> d8 = {pii(1, 1), pii(1, 0), pii(1,-1), pii(0, -1), 
													pii(-1, -1), pii(-1, 0), pii(-1, 1), pii(0, 1)};

int n, t;
pii a[kN];
map<pii, int> mp;
int adj[kN][8];

int die[kN];
vector<int> getOuter(){
	die[0] = 1;
	pii bst(-INF, -INF); int cur = -1;
	for(int i = 1; i <= n; ++i)
		if(!die[i] and chmax(bst, a[i])) cur = i;

	// (6 + 5) % 8 = 3
	int dir = 6, u = cur;
	vector<int> ans;
	do {
		dir = (dir + 5) % 8;
		ans.pb(u);
		for(int i = 0; i < 8; ++i){
			int d = (dir+i)%8, v = adj[u][d];
			if(!die[v]){
				u = v;
				dir = d;
				break;
			}
		}
	} while(u != cur);

	sort(AI(ans));
	ans.erase(unique(AI(ans)), end(ans));
	debug(ans);
	return ans;
}

int isa[kN];
int pre[kN], low[kN], tot;

void dfs(int u, int p){
	debug(u);
	pre[u] = low[u] = ++tot;
	int chi = 0, tmp = INF;
	for(int i = 0; i < 8; ++i){
		int v = adj[u][i];
		if(die[v] or v == p) continue;
		if(pre[v] == 0){
			++chi;
			dfs(v, u); 
			chmin(low[u], low[v]);
		} else chmin(tmp, pre[v]);
	}
	debug(u, chi, pre[u], low[u]);
	if(p == 0){ if(chi > 1) isa[u] = true;}
	else if(chi > 0 and low[u] >= pre[u]) isa[u] = true;
	chmin(low[u], tmp);
}

void getArt(){
	for(int i = 1; i <= n; ++i) isa[i] = 0;
	for(int i = 1; i <= n; ++i) pre[i] = 0;
	for(int i = 1; i <= n; ++i) low[i] = 0;
	tot = 0;
	for(int i = 1; i <= n; ++i)
		if(!die[i]){ dfs(i, 0); break; }
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> t;
	DSU dsu(n);

	for(int r, c, i = 1; i <= n; ++i){
		cin >> r >> c;
		a[i] = pii(r, c);
		mp[pii(r, c)] = i;
	}

	for(int i = 1; i <= n; ++i){
		auto [r, c] = a[i];
		for(int d = 0; d < 8; ++d){
			auto [dr, dc] = d8[d];
			pii u(r + dr, c + dc);
			if(mp.count(u)){
				int v = mp[u];
				dsu.M(i, v);
				adj[i][d] = v;
				debug(i, v, d);
			}
		}
	}

	if(dsu.s != 1){ cout << "NO"; return 0; }
	cout << "YES\n"; 

	vector<int> ans;
	for(int t = 0; t < n; ++t){
		vector<int> out = getOuter();
		getArt();
		for(int i = 1; i <= n; ++i) if(isa[i]) debug(i);
		while(isa[out.back()]) out.pop_back();
		int v = out.back();
		ans.pb(v);
		die[v] = true;
		debug(v);
	}

	reverse(AI(ans));
	for(int i: ans) cout << i << ' ';

	return 0;
}
