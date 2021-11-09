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
struct SGT {
	int n; vector<int> val, tag;
	SGT(int nn) : n(nn), val(nn*2, 0), tag(nn*2, 0) {}
	void upd(int p, int v){
		val[p] += v;
		if(p < n) tag[p] += v;
	}
	void push(int p){
		for(int h = __lg(n); h >= 0; --h){
			int i = p>>h;
			if(!tag[i>>1]) continue;
			upd(i, tag[i>>1]);
			upd(i^1, tag[i>>1]);
			tag[i>>1] = 0;
		}
	}
	void pull(int p){
		for(; p > 1; p >>= 1)
			val[p>>1] = min(val[p], val[p^1]) + tag[p>>1];
	}
	void modify(int l, int r, int v){
		//for(int i = l; i <= r; ++i)
		//	val[i] += v;
		int tl = l, tr = r;
		push(l += n); push(r += n); ++r;
		for(; l < r; l >>= 1, r >>= 1){
			if(l&1) upd(l++, v);
			if(r&1) upd(--r, v);
		}
		pull(tl+n); pull(tr+n);
	}
	bool query(int l, int r){
		//for(int i = l; i <= r; ++i)
		//	if(val[i] <= 0) return false;
		//return true;
		push(l += n); push(r += n); ++r;
		int mn = INT_MAX;
		for(; l < r; l >>= 1, r >>= 1){
			if(l&1) mn = min(mn, val[l++]);
			if(r&1) mn = min(mn, val[--r]);
		}
		return mn != 0;
	}
};

const int kN = 50005;
int N, R, C, t[kN], x[kN], y[kN];

int get(int l, int r, int v){
	if(v == 0){
		if(l <= R and R <= r) return R;
		if(r <= R) return r;
		return R-(l-R);
	}
	if(l <= C and C <= r) return -C;
	if(r <= C) return -r;
	return -C + (l-C);
}

bool solve(int ti){
	debug(ti);
	vector<tuple<int, int, int, int>> mods; mods.reserve(N*2);
	LISAN lx, ly; int mxy = -C, mny = R;
	for(int i = 0; i < N; ++i){
		if(ti <= t[i]) continue;
		int tk = ti - t[i];
		int l = max(    0ll, (ll) x[i]-tk), r = min((ll) R+C, (ll) x[i]+tk);
		int d = max((ll) -C, (ll) y[i]-tk), u = min((ll)   R, (ll) y[i]+tk);
		mods.pb(l, d, u, 1); mods.pb(r, d, u, -1);
		lx.pb(l); lx.pb(r);
		ly.pb(d); ly.pb(u);
		debug(tk, x[i], y[i], l, r, u, d);
	}
	debug(mods);
	if(mods.empty()) return false;
	lx.done(); if(lx[0] != 0  or lx.back() != R+C) return false;

	vector<tuple<int, int, int>> ques; ques.reserve(lx.size());
	for(int i = 1; i < lx.size(); ++i){
		//debug(lx[i-1], lx[i], get(lx[i-1], lx[i], 0)-1);
		//debug(lx[i-1], lx[i], get(lx[i-1], lx[i], 1));
		int u = get(lx[i-1], lx[i], 0) - 1;
		int d = get(lx[i-1], lx[i], 1);
		ques.pb(i, d, u);
		ly.pb(d); ly.pb(u);
	}
	ly.done();
	for(auto &[x, d, u, v]: mods){ x = lx(x); d = ly(d); u = ly(u); }
	for(auto &[x, d, u]: ques){ d = ly(d); u = ly(u); }
	sort(AI(mods));
	debug(mods);
	debug(lx, ly);

	SGT sgt(ly.size());
	int p = 0;
	for(auto &[qx, qd, qu]: ques){
		while(p < mods.size()){
			auto &[x, d, u, v] = mods[p];
			//debug(p, x, d, u, v);
			if(x >= qx) break;
			sgt.modify(d, u-1, v);
			++p;
		}
		//debug(qx, qd, qu, sgt.val);
		if(!sgt.query(qd, qu)) return false;
	}
	debug(1);
	return true;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> R >> C;

	for(int i = 0; i < N; ++i)
		cin >> t[i] >> x[i] >> y[i];

	int tmin = *min_element(t, t+N);
	for(int i = 0; i < N; ++i){
		t[i] -= tmin;
		x[i] += y[i];
		y[i] = x[i] - y[i]*2;
	}
	
	if(R == 0 and C == 0){ cout << tmin << '\n'; return 0; }

	ll ans = 0;
	for(int l = 30; l >= 0; --l)
		if(!solve(ans + (1<<l)))
			ans += (1<<l);
	++ans;

	debug(ans, tmin);
	cout << (ll) ans + tmin << '\n';
	return 0;
}

/*
 Input:
15 1113 1057
31 183 1038
124 1042 834
1628 71 361
1126 2 40
1441 291 899
6 38 223
1424 338 600
1776 142 284
1454 1050 307
1768 645 44
1445 631 708
1508 265 115
1947 1062 237
1370 388 311
107 800 96

BruteForce Output:
849

Your solution Output:
677

Input:
17 11 14
10 1 10
5 1 13
13 0 11
12 5 12
15 9 7
8 10 0
8 4 1
8 3 2
19 0 0
11 0 3
10 11 11
17 9 14
4 8 4
7 11 14
5 2 5
10 1 11
19 11 5

BruteForce Output:
13

Your solution Output:
12

 */
