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

const int N = 100001, inf = 8e7;
const ll INF = 1e18;

struct LISAN: vector<ll>{
	void done(){ sort(AI()); erase(unique(AI()), end());}
	int operator()(int v){ return lower_bound(AI(), v) - begin();}
};
struct QUERY{
	int l, r, id;
	QUERY(){}
	QUERY(int l, int r, int i):
		l(l), r(r), id(i){}
	bool operator<(const QUERY &rhs) const{
		return l > rhs.l;
	}
};
struct BIT{
	int n; vector<ll> val;
	BIT(){}
	BIT(int _n){
		n = _n;
		val.assign(n + 1, INF);
	}
	void modify(int p, ll v){ for(++p; p <= n; p += p & -p) chmin(val[p], v); }
	ll query(int p){ ll r = INF; for(++p; p > 0; p -= p & -p) chmin(r, val[p]); return r;}
};
struct ZCK{
	int n; vector<int> val;
	ZCK(){}
	ZCK(int _n){
		n = _n;
		val.assign(n * 2 + 1, inf);
	}
	void modify(int p, int v){ for(val[p += n] = v; p > 1; p >>= 1) val[p >> 1] = min(val[p], val[p ^ 1]); }
	int query(int l, int r){
		int ans = inf;
		for(l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l & 1) chmin(ans, val[l++]);
			if(r & 1) chmin(ans, val[--r]);
		}
		return ans;
	}
};

void solve(int n, vector<ll> &a, vector<QUERY> &qs, vector<ll> &ans){
	// iterate i backward
	// for each i, find j s.t.
	// - i < j
	// - a[i] < a[j]
	// and then update answer for j
	// 
	// for each query [l, r]
	// the answer will be bit.query(0, r)
	// cause (0, l) must be undone
	//
	// sort queries
	// curpos = n - 1
	// for(queries)
	//   update curpos to l
	//   chmin answer
	
	sort(AI(qs));
	LISAN lis; for(ll i: a) lis.pb(i);
	lis.done();

	BIT bit(n);
	ZCK zck(n);

	int pos = n;
	for(auto [l, r, id]: qs){
		while(l < pos){
			--pos;
			int nxt = zck.query(lis(a[pos]), n);
			while(nxt != inf){
				bit.modify(nxt, abs(a[pos] - a[nxt]));
				if(a[pos] == a[nxt]) break;

				ll v = (a[pos] + a[nxt]) / 2;
				int p = upper_bound(AI(lis), v) - begin(lis);
				nxt = zck.query(lis(a[pos]), p);
			}
			zck.modify(lis(a[pos]), pos);
		}
		chmin(ans[id], bit.query(r));
	}
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	int n; cin >> n;
	vector<ll> a(n);
	for(int i = 0; i < n; ++i) cin >> a[i];

	int q; cin >> q;
	vector<QUERY> qs;
	for(int i = 0, l, r; i < q; ++i){
		cin >> l >> r;
		qs.pb(l - 1, r - 1, i);
	}

	vector<ll> ans(q, INF);

	solve(n, a, qs, ans);

	reverse(AI(a));
	for(auto &[l, r, i]: qs){
		l = n - l - 1;
		r = n - r - 1;
		swap(l, r);
	}
	solve(n, a, qs, ans);

	for(int i = 0; i < q; ++i) cout << ans[i] << '\n';
	return 0;
}
