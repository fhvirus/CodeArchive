// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb emplace_back
#define AI(x) begin(x),end(x)
#pragma GCC optimize("Ofast")

struct LISAN : vector<int> {
	void done() { sort(AI()); erase(unique(AI()), end()); }
	int operator () (int v) { return lower_bound(AI(), v) - begin(); }
	int ub (int v) { return upper_bound(AI(), v) - begin(); }
};
struct SGT {
	int n; vector<int> val, tag;
	SGT(int nn) : n(nn), val(nn*2+2, 0), tag(nn*2+2, 0) {}
	[[ gnu::pure ]] const int id(int l, int r){ return (l+r)|(l!=r); }
	void modify(int l, int r, int ql, int qr, int v){
		int i = id(l, r);
		if(ql <= l and r <= qr){ val[i] += v; return; }
		int m = (l+r)/2;
		if(ql <= m) modify(l, m, ql, qr, v);
		if(m < qr) modify(m+1, r, ql, qr, v);
		tag[i] = (tag[id(l, m)] or val[id(l, m)])
			and (tag[id(m+1, r)] or val[id(m+1, r)]);
	}
	bool query(int l, int r, int ql, int qr){
		int i = id(l, r);
		if(val[i]) return true;
		if(ql <= l and r <= qr) return tag[i];
		int m = (l+r)/2;
		return (ql <= m ? query(l, m, ql, qr) : 1)
			and (m < qr ? query(m+1, r, ql, qr) : 1);
	}
	void modify(int ql, int qr, int v){ modify(1, n, ql, qr, v); }
	bool query(int ql, int qr){ return query(1, n, ql, qr); }
};

const int kN = 50005;
int N, R, C, t[kN], x[kN], y[kN];

int get(int l, int r, int v){
	if(v == 0){
		if(l <= R and R <= r) return R;
		return (r <= R ? r : R-(l-R));
	}
	if(l <= C and C <= r) return -C;
	return (r <= C ? -r : (l-C)-C);
}

const int min(int a, ll b){ return a < b ? a : (int) b; }
const int max(int a, ll b){ return a > b ? a : (int) b; }
vector<tuple<int, int, int, int>> mods;
bool solve(int ti){
	mods.clear();
	LISAN ly;
	for(int i = 0; i < N; ++i){
		if(ti <= t[i]) continue;
		int tk = ti - t[i];
		int l = max( 0, (ll) x[i]-tk), r = min(R+C, (ll) x[i]+tk);
		int d = max(-C, (ll) y[i]-tk), u = min(  R, (ll) y[i]+tk);
		mods.pb(l, d, u, 1); mods.pb(r, d, u, -1);
		ly.pb(d); ly.pb(u);
	}
	sort(AI(mods));
	if(mods.empty() or get<0>(mods[0]) > 0 or get<0>(mods.back()) < R+C) return false;
	ly.done(); if(ly[0] > -C or ly.back() < R) return false;

	SGT sgt(ly.size());
	for(int i = 0, j = 0; i < (int) mods.size(); i = j){
		for(j = i; j < mods.size() and get<0>(mods[i]) == get<0>(mods[j]); ++j){
			auto &[x, d, u, v] = mods[j];
			d = ly.ub(d); u = ly(u);
			sgt.modify(d, u, v);
		}
		if(j == (int) mods.size()) break;
		int cu, nx, qd, qu;
		cu = get<0>(mods[i]);
		nx = get<0>(mods[j]);
		qd = ly.ub(get(cu, nx, 1));
		qu = ly(get(cu, nx, 0));
		if(!sgt.query(qd, qu)) return false;
	}
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
		if((1<<l) <= R+C and !solve(ans + (1<<l)))
			ans += (1<<l);
	++ans;

	cout << (ll) ans + tmin << '\n';
	return 0;
}
