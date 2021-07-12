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

struct SEG {
	struct NOD {
		int lft, rgt, mxv;
		NOD *lc, *rc;
		NOD(int len = 0): lft(len), rgt(len), mxv(len), lc(0), rc(0) {}
	};

	int n;
	NOD *rt;
	void init(int nn, vector<int> one){
		n = nn;
		for(auto i: one) mod(rt, 0, n, i, 1);
	}
	void mod(int p, int v){ mod(rt, 0, n, p, v); }
	int que(int l, int r){
		auto [al, ar, ans] = que(rt, 0, n, l, r);
		return ans;
	}

	void mod(NOD *&nd, int l, int r, int p, int v){
		if(!nd){ nd = new NOD(r - l); }
		if(l + 1 == r){
			nd->lft = nd->rgt = nd->mxv = (1 - v);
			return;
		}
		int m = (l + r) / 2;
		NOD *&lc = nd->lc, *&rc = nd->rc;
		if(p < m) mod(lc, l, m, p, v);
		else      mod(rc, m, r, p, v);

		// pull
		nd->lft = ((!lc or lc->mxv == m - l) ? (m - l) + (rc ? rc->lft : r - m) : lc->lft);
		nd->rgt = ((!rc or rc->mxv == r - m) ? (r - m) + (lc ? lc->rgt : m - l) : rc->rgt);
		nd->mxv = max(nd->lft, nd->rgt);
		if(lc and rc) chmax(nd->mxv, lc->rgt + rc->lft);
		if(lc) chmax(nd->mxv, lc->mxv);
		if(rc) chmax(nd->mxv, rc->mxv);
	}
	typedef tuple<int, int, int> tii;
	tii que(NOD *&nd, int l, int r, int ql, int qr){
		if(!nd or nd->mxv == r - l){
			int len = min(qr, r) - max(ql, l);
			return tii(len, len, len);
		}
		if(ql <= l and r <= qr) return tie(nd->lft, nd->rgt, nd->mxv);
		int m = (l + r) / 2;
		if(qr <= m) return que(nd->lc, l, m, ql, qr);
		if(ql >  m) return que(nd->rc, m, r, ql, qr);
		auto [lcl, lcr, lcv] = que(nd->lc, l, m, ql, qr);
		auto [rcl, rcr, rcv] = que(nd->rc, m, r, ql, qr);
		int al = (lcv == m - l ? m - l + rcl : lcl);
		int ar = (rcv == r - m ? r - m + lcr : rcr);
		int av = max({al, ar, lcv, rcv, lcr + rcl});
		return tii(al, ar, av);
	}
};

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n, q, c; cin >> n >> q >> c;
	vector<int> a(n);
	map<int, vector<int>> mp;
	for(int i = 0; i < n; ++i){
		cin >> a[i];
		if(!mp.count(a[i])) mp[a[i]] = vector<int>();
		mp[a[i]].pb(i);
	}
	map<int, SEG> sgs;
	for(auto [i, v]: mp){
		sgs[i] = SEG();
		sgs[i].init(n, v);
	}

	for(int cmd, l, r, p, k; q; --q){
		cin >> cmd;
		if(cmd == 0){
			cin >> p >> k;
			sgs[a[p]].mod(p, 0);
			if(sgs.count(k)) sgs[k].mod(p, 1);
			else{ sgs[k] = SEG(); sgs[k].init(n, vector<int>(1, p)); }
			a[p] = k;
		} else {
			cin >> l >> r >> k;
			if(!sgs.count(k)) cout << r - l << '\n';
			else cout << sgs[k].que(l, r) << '\n';
		}
	}
	return 0;
}
