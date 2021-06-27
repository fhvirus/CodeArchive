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

const ll INF = 1e18;
const int kN = 100001;

struct EEK {
	int d, p, r, g;
	EEK(){}
	EEK(int d, int p, int r, int g):
		d(d), p(p), r(r), g(g){}
	const bool operator< (const EEK &rhs) const { return d < rhs.d; }
};

struct SEG {
	ll m, k;
	SEG(ll m = 0, ll k = 0): m(m), k(k){}
	const ll operator() (int x) const { return m * x + k; }
};

struct SGT {
	struct NOD {
		SEG seg;
		int lc, rc;
		NOD(): lc(0), rc(0) {}
		NOD(ll m, ll k): seg(m, k), lc(0), rc(0) {}
	} nds[kN];
	int n, rt, cnt = 1;
	void init(int nn){ n = nn, rt = cnt++; }
	int newNode(ll m, ll k){ nds[cnt] = NOD(m, k); return cnt++; }
	void ins(int &nd, int l, int r, SEG seg){ 
		if(nd == 0){
			nd = newNode(seg.m, seg.k);
			return;
		}
		if(l == r){
			if(nds[nd].seg(l) < seg(l)) nds[nd].seg = seg;
			return;
		}
		int m = (l + r) / 2;
		if(nds[nd].seg(m) < seg(m)) swap(nds[nd].seg, seg);
		if(seg.m < nds[nd].seg.m) ins(nds[nd].lc, l, m, seg);
		else ins(nds[nd].rc, m+1, r, seg);
	}
	void ins(ll m, ll k){ ins(rt, 0, n, SEG(m, k)); }
	ll que(int nd, int l, int r, int p){
		if(nd == 0) return -INF;
		if(l == r) return nds[nd].seg(p);
		int m = (l + r) / 2;
		return max(nds[nd].seg(p), p <= m ? que(nds[nd].lc, l, m, p) : que(nds[nd].rc, m+1, r, p));
	}
	ll que(int p){ return que(rt, 0, n, p); }
} sgt;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n, c, d; cin >> n >> c >> d;

	vector<EEK> eek;
	eek.pb(d + 1, 0, 0, 0);
	for(int i = 0, d, p, r, g; i < n; ++i){
		cin >> d >> p >> r >> g;
		eek.pb(d, p, r, g);
	}
	sort(AI(eek));

	sgt.init(d + 1);
	sgt.ins(0, c);
	ll dp;
	for(int i = 0; i <= n; ++i){
		auto [d, p, r, g] = eek[i];
		dp = sgt.que(d) - p;
		if(dp >= 0) sgt.ins(g, dp + r - 1ll * (d+1) * g);
	}
	cout << dp;
	return 0;
}
