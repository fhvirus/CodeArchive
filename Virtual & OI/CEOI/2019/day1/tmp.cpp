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

int n, q; ll w;
pii edg[kN];
ll  wei[kN];
vector<pii> adj[kN];
int in[kN], ou[kN], tot;
ll eu[kN * 2];

struct NOD {
	ll mnv, mxv, lft, rgt, ans, tag;
	NOD(ll v = 0): mnv(v), mxv(v), lft(-v), rgt(-v), ans(0), tag(0) {}
} nod[kN * 4];
void merge(NOD l, NOD r, NOD &u){
	u.mnv = min(l.mnv, r.mnv);
	u.mxv = max(l.mxv, r.mxv);
	u.lft = max({ l.lft, r.lft, l.mxv - 2 * r.mnv });
	u.rgt = max({ l.rgt, r.rgt, r.mxv - 2 * l.mnv });
	u.ans = max({ l.ans, r.ans, l.lft + r.mxv, l.mxv + r.rgt });
}

inline int id(int l, int r){ return (l + r) | (l != r); }
void build(int l, int r){
	int i = id(l, r);
	if(l == r){ nod[i] = NOD(eu[l]); return; }
	int m = (l + r) / 2;
	build(l, m);
	build(m+1, r);
	merge(nod[id(l, m)], nod[id(m+1, r)], nod[i]);
}
void upd(NOD &u, ll v){
	u.mnv += v;
	u.mxv += v;
	u.lft -= v;
	u.rgt -= v;
	u.tag += v;
}
void push(NOD &u, int l, int r){
	int m = (l + r) / 2;
	int lc = id(l, m), rc = id(m+1, r);
	upd(nod[lc], u.tag);
	upd(nod[rc], u.tag);
	u.tag = 0;
}
void modify(int l, int r, int ql, int qr, ll v){
	int i = id(l, r);
	if(l == r){ upd(nod[i], v); return; }
	push(nod[i], l, r);
	if(ql <= l and r <= qr){
		upd(nod[i], v);
		push(nod[i], l, r);
		return;
	}
	int m = (l + r) / 2;
	if(ql <= m) modify(l, m, ql, qr, v);
	if(m+1 <= qr) modify(m+1, r, ql, qr, v);
	merge(nod[id(l, m)], nod[id(m+1, r)], nod[i]);
}

void dfs(int u, int p = 0, ll d = 0){
	in[u] = tot; eu[tot++] = d;
	for(auto [v, i]: adj[u]){
		if(v == p) continue;
		if(edg[i].ff == v) swap(edg[i].ff, edg[i].ss);
		dfs(v, u, d + wei[i]);
		eu[tot++] = d;
	}
	ou[u] = tot - 1;
}
void init(){
	dfs(1);
	build(0, tot - 1);
}
ll upd(int d, ll e){
	int u = edg[d].ss;
	ll  v = e - wei[d];
	modify(0, tot-1, in[u], ou[u], v);
	return nod[id(0, tot-1)].ans;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> q >> w;
	for(int i = 0; i < n-1; ++i){
		int u, v; ll c; cin >> u >> v >> c;
		edg[i] = pii(u, v);
		wei[i] = c;
		adj[u].pb(v, i);
		adj[v].pb(u, i);
	}
	init();
	ll last = 0;
	for(int i = 0; i < q; ++i){
		ll d, e; cin >> d >> e;
		d = (d + last) % (n-1);
		e = (e + last) % w;
		last = upd(d, e);
		cout << last << '\n';
	}
	return 0;
}

