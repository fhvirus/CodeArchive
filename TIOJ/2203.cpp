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

const int kN = 100000;
const int kC = 1'000'000'000;
const int MOD = 1'000'000'007;
const int INV2 = (MOD+1)/2;

inline int mad(int u, int v){
	u += v - MOD;
	u += MOD & (u >> 31);
	return u;
}
template<typename...T> inline int mad(int u, T...t){
	return mad(u, mad(t...));
}
inline int mul(int u, int v){
	return (ll) u * v % MOD;
}
template<typename...T> inline int mul(int u, T...t){
	return mul(u, mul(t...));
}
constexpr int id(int l, int r){ return (l+r) | (l!=r); }

struct NODE {
	int m, v, mv, v2, mv2, tm, tv;
	NODE(int m = 0, int v = 0):
		m(m), v(v), mv(mul(m, v)), v2(mul(v, v)),
		mv2(mul(m, v2)), tm(0), tv(0) {}
} nds[(kN+1)*2];

int N, Q;
int m[kN+1], v[kN+1];

void upd(int i, int len, int dm, int dv){
	NODE &u = nds[i];
	u.mv2 = mad(u.mv2, mul(2, dv, u.mv), mul(dv, dv, u.m),
			mul(dm, u.v2), mul(2, dm, dv, u.v), mul(len, dm, dv, dv));
	u.mv = mad(u.mv, mul(dv, u.m), mul(dm, u.v), mul(len, dm, dv));
	u.v2 = mad(u.v2, mul(2, dv, u.v), mul(len, dv, dv));
	u.m = mad(u.m, mul(len, dm));
	u.v = mad(u.v, mul(len, dv));
	u.tm = mad(u.tm, dm);
	u.tv = mad(u.tv, dv);
}
void push(int i, int l, int r){
	NODE &u = nds[i]; int m = (l+r) / 2;
	upd(id(l, m), m-l+1, u.tm, u.tv);
	upd(id(m+1, r), r-m, u.tm, u.tv);
	u.tm = u.tv = 0;
}
void pull(int i, int l, int r){
	NODE &u = nds[i], &lc = nds[l], &rc = nds[r];
	u.m = mad(lc.m, rc.m);
	u.v = mad(lc.v, rc.v);
	u.mv = mad(lc.mv, rc.mv);
	u.v2 = mad(lc.v2, rc.v2);
	u.mv2 = mad(lc.mv2, rc.mv2);
}

void init(int l, int r){
	int i = id(l, r);
	if(l == r){ nds[i] = NODE(m[l], v[l]); return; }
	int m = (l+r) / 2;
	init(l, m); init(m+1, r);
	pull(i, id(l, m), id(m+1, r));
}
void modify(int l, int r, int ql, int qr, int dm, int dv){
	int i = id(l, r);
	if(ql <= l and r <= qr){
		upd(i, r-l+1, dm, dv);
		return;
	}
	push(i, l, r);
	int m = (l+r) / 2;
	if(ql <= m) modify(l, m, ql, qr, dm, dv);
	if(m+1 <= qr) modify(m+1, r, ql, qr, dm, dv);
	pull(i, id(l, m), id(m+1, r));
}
int query(int l, int r, int ql, int qr){
	int i = id(l, r);
	if(ql <= l and r <= qr) return nds[i].mv2;
	push(i, l, r); 
	int m = (l+r) / 2, res = 0;
	if(ql <= m) res = mad(res, query(l, m, ql, qr));
	if(m+1 <= qr) res = mad(res, query(m+1, r, ql, qr));
	return res;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	assert(cin >> N >> Q);
	assert(1 <= N and N <= kN);
	assert(1 <= Q and Q <= kN);

	for(int i = 1; i <= N; ++i){
		assert(cin >> m[i]);
		assert(0 <= m[i] and m[i] <= kC);
	}
	for(int i = 1; i <= N; ++i){
		assert(cin >> v[i]);
		assert(0 <= v[i] and v[i] <= kC);
	}

	init(1, N);

	int queryNum = 0;
	for(int i = 0; i < Q; ++i){
		int t, l, r, x, y;
		assert(cin >> t);
		assert(1 <= t and t <= 3);
		if(t == 1){
			assert(cin >> l >> r >> x);
			assert(1 <= l and l <= r and r <= N);
			assert(0 <= x and x <= kC);
			modify(1, N, l, r, x, 0);
		} else if(t == 2){
			assert(cin >> l >> r >> y);
			assert(0 <= l and l <= r and r <= N);
			assert(0 <= y and y <= kC);
			modify(1, N, l, r, 0, y);
		} else {
			assert(cin >> l >> r);
			assert(0 <= l and l <= r and r <= N);
			cout << mul(query(1, N, l, r), INV2) << '\n';
			++queryNum;
		}
	}

	assert(queryNum > 0);

	return 0;
}

