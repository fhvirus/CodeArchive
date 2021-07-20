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

struct LISAN : vector<int> {
	void done(){ sort(AI()); erase(unique(AI()), end()); }
	int operator() (int v) { return lower_bound(AI(), v) - begin(); }
};
struct SGT {
	int n; vector<pii> val;
	constexpr int id(int l, int r){ return (l + r - 2) | (l != r); }
	void init(int l, int r, int v){
		if(l == r){ val[id(l, r)] = pii(v, -l); return; }
		int m = (l + r) / 2;
		init(l, m, v);
		init(m+1, r, v);
		val[id(l, r)] = max(val[id(l, m)], val[id(m+1, r)]);
	}
	void init(int nn, int v){
		n = nn;
		val.resize(n * 2);
		init(1, n, v);
		debug(val);
	}
	void mdf(int l, int r, int p, int v){
		if(l == r){ val[id(l, r)] = pii(v, -l); return; }
		int m = (l + r) / 2;
		if(p <= m) mdf(l, m, p, v);
		else mdf(m+1, r, p, v);
		val[id(l, r)] = max(val[id(l, m)], val[id(m+1, r)]);
	}
	void mdf(int p, int v){ mdf(1, n, p, v); }
	pii que(){
		auto [v, p] = val[id(1, n)];
		return pii(-p, v);
	}
};

int N, T, M, Q;
LISAN lisan;
vector<tuple<int, int, int>> ms;
vector<int> qs;

vector<vector<pii>> mdf;
vector<int> cnt;
vector<pii> ans;
SGT sgt;

void solve() {
	cin >> M;
	ms.clear();
	lisan.clear();
	qs.clear();

	for(int i = 0, p, a, b; i < M; ++i){
		cin >> p >> a >> b;
		ms.pb(p, a, b);
		lisan.pb(a); lisan.pb(b);
	}

	cin >> Q;
	for(int i = 0, t; i < Q; ++i){
		cin >> t;
		qs.pb(t);
		lisan.pb(t);
	}

	lisan.done();
	mdf.assign(lisan.size(), vector<pii>());
	cnt.assign(N + 1, 0);
	ans.assign(lisan.size(), pii(0, 0));
	sgt.init(N, T);

	debug(lisan);

	for(auto [i, a, b]: ms){
		a = lisan(a); b = lisan(b);
		mdf[a].pb(i, -1);
		mdf[b].pb(i, 1);
	}

	for(int i = lisan.size() - 1; i >= 0; --i){
		auto [p, v] = sgt.que();
		debug(i, lisan[i], p, v);
		ans[i] = pii(p, v - lisan[i]);
		for(auto [p, v]: mdf[i]){
			if(cnt[p] == 0) sgt.mdf(p, -1);
			if(cnt[p] == 1 and v == -1) sgt.mdf(p, lisan[i]);
			cnt[p] += v;
		}
		debug(cnt);
	}

	for(int i: qs){
		i = lisan(i);
		if(ans[i].ss <= 0) cout << "Oh, no!\n";
		else cout << ans[i].ff << ' ' << ans[i].ss << '\n';
	} 
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	while(cin >> N >> T && N && T) solve();
	return 0;
}
