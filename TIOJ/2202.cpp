// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll;
typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}

const int N = 100001;
const int C = 100001;
const int K = 320;
const ll INF = 4e18;

int n, q;
vector<int> a, w;
vector<ll> ans;

// qa: l, r, how many more, discarded, index
// qb: l, r, how many less, ciscarded, index
struct Query{
	int l, r, x, y, i;
	Query(){}
	Query(int l, int r, int x, int y, int i):
		l(l), r(r), x(x), y(y), i(i){}
	bool operator<(const Query &rhs){
		if(l / K == rhs.l / K) return r < rhs.r;
		return l / K < rhs.l / K;
	}
};
struct CountMo{
	vector<int> cnt;
	int ans, l, r;
	CountMo(){
		ans = 0;
		l = r = 0;
		cnt.assign(C, 0);
	}
	void add(int p){
		int v = a[p];
		if(cnt[v] == 0) ++ans;
		++cnt[v];
	}
	void del(int p){
		int v = a[p];
		--cnt[v];
		if(cnt[v] == 0) --ans;
	}
	void move(int ql, int qr){
		while(l > ql) add(--l);
		while(r < qr) add(++r);
		while(l < ql) del(l++);
		while(r > qr) del(r--);
	}
};
void divide(vector<Query> &qs, vector<Query> &qa, vector<Query> &qb){
	CountMo mo;
	sort(AI(qs));
	for(Query qi: qs){
		mo.move(qi.l, qi.r);
		if(mo.ans < qi.x) qa.pb(qi.l, qi.r, qi.x - mo.ans, 0, qi.i);
		if(mo.ans > qi.y) qb.pb(qi.l, qi.r, mo.ans - qi.y, 0, qi.i);
	}
}

struct RollbackMo{
	// query: choose min k cost
	// but reserve one max for every number
	constexpr int bk(int p){ return p / K;}
	int l, r, plb;
	vector<int> mxc, a0;
	vector<pair<int, ll>> a1;
	vector<pii> mxcm;
	vector<int> cntm;
	RollbackMo(){
		l = r = 0;
		plb = -1;
		mxc.assign(C, 0);
		a0.assign(C, 0);
		a1.assign(C / K + 1, {0, 0});
	}
	void ins(int v){
		a0[v]++;
		a1[bk(v)].ff++; a1[bk(v)].ss += v;
	}
	void del(int v){
		a0[v]--;
		a1[bk(v)].ff--; a1[bk(v)].ss -= v;
	}
	void clear(){
		mxc.assign(C, 0);
		a0.assign(C, 0);
		a1.assign(C / K + 1, {0, 0});
	}
	void adr(int p){
		int v = a[p];
		int c = w[p];
		if(mxc[v] < c) swap(mxc[v], c);
		if(c != 0) ins(c);
	}
	void adl(int p){
		int v = a[p];
		int c = w[p];
		if(mxc[v] < c){
			swap(mxc[v], c);
			mxcm.pb(v, c);
		}
		if(c != 0){
			cntm.pb(c);
			ins(c);
		}
	}
	void undo(){
		while(!mxcm.empty()){
			auto [p, v] = mxcm.back();
			mxcm.pop_back();
			mxc[p] = v;
		}
		while(!cntm.empty()){
			del(cntm.back());
			cntm.pop_back();
		}
	}
	ll curans(int k){
		ll sum = 0;
		int cur = 0;
		int i = 0;
		for(; i < a1.size(); ++i){
			if(cur + a1[i].ff > k) break;
			cur += a1[i].ff;
			sum += a1[i].ss;
		}
		if(cur == k) return sum;
		i = i * K;
		for(; i < a0.size(); ++i){
			int lft = min(a0[i], k - cur);
			cur += lft;
			sum += 1ll * lft * i;
			if(cur == k) break;
		}
		return sum;
	}
	ll query(int ql, int qr, int k){
		if(qr - ql + 1 <= K){
			vector<int> ver;
			map<int, int> mp;
			for(int i = ql; i <= qr; ++i){
				if(!mp.count(a[i])){
					mp[a[i]] = w[i];
					continue;
				}
				ver.pb(min(mp[a[i]], w[i]));
				chmax(mp[a[i]], w[i]);
			}
			nth_element(begin(ver), begin(ver) + k - 1, end(ver));
			ll ans = 0;
			for(int i = 0; i < k; ++i) ans += ver[i];
			return ans;
		}
		if(bk(ql) != plb){
			clear();
			plb = bk(ql);
			l = (bk(ql) + 1) * K;
			r = l - 1;
		}
		int jizz = l;
		while(r < qr) adr(++r);
		while(l > ql) adl(--l);
		ll ans = curans(k);
		undo();
		l = jizz;
		return ans;
	}
};
void conquerA(vector<Query> &qs){
	RollbackMo mo;
	// no need to sort, cause it's done
	for(Query qi: qs){
		ans[qi.i] = mo.query(qi.l, qi.r, qi.x);
	}
}

struct BlockMo{
	// query: choose min k cost
	// cost: sum of the costs of the number
	// K1: #(val > K1) < N * C / K1
	static const int K1 = 32000000;
	static const int K2 = 100160;
	static const int K3 = 320;
	static const int TB = 1ll * N * C / K1 + 1;
	constexpr int bk1(int p){ return p / K3;}
	constexpr int bk2(int p){ return p / K2;}
	// pair<int, ll> : cnt, sum
	int l, r;
	vector<ll> val;
	vector<int> a0;
	vector<pair<int, ll>> a1, a2;
	vector<ll> tb;
	vector<int> id, va;
	BlockMo(){
		l = r = 0;
		val.assign(C, 0);
		a0.assign(K1 + 1, 0);
		a1.assign(K1 / K3 + 1, {0, 0});
		a2.assign(K1 / K2 + 1, {0, 0});
		tb.assign(TB, INF);
		va.assign(TB, 0); iota(AI(va), 0);
		id.assign(C, -1);
	}
	void ins(int p){
		ll v = val[p];
		if(v > K1){
			id[p] = va.back();
			va.pop_back();
			tb[id[p]] = v;
			return;
		}
		++a0[v];
		++a1[bk1(v)].ff; a1[bk1(v)].ss += v;
		++a2[bk2(v)].ff; a2[bk2(v)].ss += v;
	}
	void rem(int p){
		ll v = val[p];
		if(v > K1){
			tb[id[p]] = INF;
			va.pb(id[p]);
			id[p] = -1;
			return;
		}
		if(a0[v] <= 0) return;
		--a0[v];
		--a1[bk1(v)].ff; a1[bk1(v)].ss -= v;
		--a2[bk2(v)].ff; a2[bk2(v)].ss -= v;
	}
	void add(int p){
		int v = a[p];
		rem(v);
		val[v] += w[p];
		ins(v);
	}
	void del(int p){
		int v = a[p];
		rem(v);
		val[v] -= w[p];
		if(val[v] != 0) ins(v);
	}
	void move(int ql, int qr){
		while(l > ql) add(--l);
		while(r < qr) add(++r);
		while(l < ql) del(l++);
		while(r > qr) del(r--);
	}
	ll query(int k){
		ll ans = 0;
		int cur = 0;
		// look up a2
		// if still too few, turn to br
		int i = 0;
		for(; i < a2.size(); ++i){
			if(cur + a2[i].ff > k) break;
			cur += a2[i].ff;
			ans += a2[i].ss;
		}
		if(i == a2.size() and cur < k){
			vector<ll> tmp = tb;
			nth_element(begin(tmp), begin(tmp) + k - cur - 1, end(tmp));
			for(i = 0; i < k - cur; ++i) ans += tmp[i];
			return ans;
		}
		// look up a1
		i = i * K2 / K3;
		for(; i < a1.size(); ++i){
			if(cur + a1[i].ff > k) break;
			cur += a1[i].ff;
			ans += a1[i].ss;
		}
		// look up a0
		i = i * K3;
		for(; i < a0.size(); ++i){
			int lft = min(a0[i], k - cur);
			cur += lft;
			ans += 1ll * i * lft;
			if(cur == k) break;
		}
		return ans;
	}
};
void conquerB(vector<Query> &qs){
	BlockMo mo;
	// no need to sort, cause it's done
	for(Query qi: qs){
		mo.move(qi.l, qi.r);
		ans[qi.i] = mo.query(qi.x);
	}
}

void combine(){
	for(int i = 0; i < q; ++i)
		cout << ans[i] << '\n';
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	cin >> n >> q;
	a.resize(n + 1);
	w.resize(n + 1);
	ans.assign(q, 0);
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 1; i <= n; ++i) cin >> w[i];

	// qs: all
	// qa: too few
	// qb: too much
	vector<Query> qs, qa, qb;
	for(int i = 0, l, r, x, y; i < q; ++i){
		cin >> l >> r >> x >> y;
		qs.pb(l, r, x, y, i);
	}

	divide(qs, qa, qb);

	conquerA(qa);
	conquerB(qb);

	combine();

	return 0;
}
