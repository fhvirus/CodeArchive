// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll;
typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define OOF(i,a,b) for(int i=(a);i>=int(b);--i)
#define AI(x) (x).begin(),(x).end()
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
template<class V>void lisan(V&v){sort(AI(v));v.erase(unique(AI(v)),v.end());}
template<class V,class T>int lspos(const V&v,T x){return lower_bound(AI(v),x)-v.begin();}
template<class...T>void RI(T&...t){(...,(cin>>t));}
template<class...T>void PL(T...t){int c=sizeof...(T);if(!c){cout<<'\n';return;}(...,(cout<<t<<(--c?' ':'\n')));}
constexpr inline ll cdiv(ll x,ll m){return x/m+(x%m?(x<0)^(m>0):0);}
constexpr inline ll mpow(ll x,ll e,ll m){ll r=1;for(x%=m;e;e/=2,x=x*x%m)if(e&1)r=r*x%m;return r;}
#ifdef OWO
#define safe cerr<<"\033[1;32m"<<__PRETTY_FUNCTION__<<" - "<<__LINE__<<" JIZZ\033[0m\n"
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}
template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
#else
#pragma GCC optimize("Ofast")
#include"lib1273.h"
#define safe ((void)0)
#define debug(...) ((void)0)
#endif
constexpr ll inf = 1e9, INF = 4e18;

struct DSU{
	vector<int> g, s;
	DSU(int n){
		g.resize(n), s.resize(n, 1), iota(AI(g), 0);
	}
	int F(int a){ return a == g[a] ? a : g[a] = F(g[a]);}
	bool M(int a, int b){
		a = F(a), b = F(b);
		if(a == b) return false;
		if(s[a] < s[b]) swap(a, b);
		s[a] += s[b], g[b] = a;
		return true;
	}
	int S(int a){ return s[F(a)];}
	int operator()(int a){ return F(a);}
};

const int maxn = 1e5 + 225;
ll subsz[maxn];
vector<pii> edges;
vector<int> adj[maxn];
vector<vector<pii>> col;
map<pii, int> pos;
ll dfs(int u, ll allsz, int p = -1){
	ll ans = 0;
	for(int v: adj[u]){
		if(v != p){
			ans += dfs(v, allsz, u);
			subsz[u] += subsz[v];
		}
	}
	return ans + subsz[u] * (allsz - subsz[u]);
}
inline ll cal(int N, int nx, int *X, int *Y){
	DSU D(N);
	edges.clear();
	// make vertex
	{
		col.resize(nx);
		FOR(i,nx) col[i].clear();
		FOR(i,N) col[X[i]].pb(Y[i], i);
		for(auto &vec: col){
			sort(AI(vec));
			FOO(i,1,vec.size()-1)
				if(vec[i-1].ff + 1 == vec[i].ff)
					D.M(vec[i-1].ss, vec[i].ss);
		}
	}
	// make edges
	{
		pos.clear();
		auto upd = [&pos, &D](int i, int x, int y){
			if(!pos.count({x, y})) return;
			int j = pos[{x, y}];
			i = D(i), j = D(j);
			if(i > j) swap(i, j);
			edges.pb(i, j);
		};
		FOR(i,N){
			int x = X[i], y = Y[i];
			upd(i, x + 1, y), upd(i, x - 1, y);
			pos[{x, y}] = i;
		}
	}
	lisan(edges);
	// make graph
	FOR(i,N) adj[i].clear(), subsz[i] = D.S(i);
	for(auto [u, v]: edges) adj[u].pb(v), adj[v].pb(u);
	// dfs
	return dfs(D(0), N);
}
inline int eek(int N, int *a){
	vector<int> v(N);
	int mn = *min_element(a, a + N);
	FOR(i,N) a[i] -= mn, v[i] = a[i];
	lisan(v); return v.size();
}
int DistanceSum(int N, int *X, int *Y){
	int nx = eek(N, X), ny = eek(N, Y);
	return (cal(N, nx, X, Y) + cal(N, ny, Y, X)) % 1'000'000'000ll;
}

#ifdef OWO
const int N = 1e5 + 225;
int n, x[N], y[N];
int DistanceSum(int N, int *X, int *Y);
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	FOR(i,n) cin >> x[i] >> y[i];
	cout << DistanceSum(n, x, y) << endl;
	return 0;
}
#endif