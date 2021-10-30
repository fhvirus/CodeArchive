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
	void done() { sort(AI()); erase(unique(AI()), end()); }
	int operator () (int v) { return lower_bound(AI(), v) - begin(); }
};
struct BIT {
	int n; vector<int> val;
	BIT (int n = 0) : n(n), val(n+1, 0) {}
	void modify(int p, int v){
		for(++p; p <= n; p += p&-p)
			val[p] += v;
	}
	int query(int p){
		int r = 0;
		for(++p; p > 0; p -= p&-p)
			r += val[p];
		return r;
	}
	int query(int l, int r){
		return query(r) - query(l-1);
	}
};
 
signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n; cin >> n;
	vector<tuple<int, int, int>> ver, hor;
	LISAN lx, ly;
	for(int x1, y1, x2, y2, i = 0; i < n; ++i){
		cin >> x1 >> y1 >> x2 >> y2;
		lx.pb(x1); if(x1 != x2) lx.pb(x2);
		ly.pb(y1); if(y1 != y2) ly.pb(y2);
		if(x1 == x2) ver.pb(x1, y1, y2);
		else hor.pb(y1, x1, x2);
	}
	lx.done(); ly.done();
	for(auto &[x, y1, y2]: ver){ x = lx(x); y1 = ly(y1); y2 = ly(y2); }
	for(auto &[y, x1, x2]: hor){ y = ly(y); x1 = lx(x1); x2 = lx(x2); }
	sort(AI(hor));
 
	vector<vector<pii>> mods(ly.size() + 1);
	BIT bit(lx.size() + 1);
	for(auto [x, y1, y2]: ver){
		mods[y1].pb(x,  1);
		mods[y2].pb(x, -1);
	}
	int ptr = -1;
	ll ans = 0;
	for(auto [y, x1, x2]: hor){
		while(ptr < y){
			++ptr;
			for(auto [p, v]: mods[ptr])
				bit.modify(p, v);
		}
		ans += bit.query(x1, x2);
	}
	cout << ans << '\n';
	return 0;
}
