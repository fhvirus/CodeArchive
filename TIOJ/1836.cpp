#pragma GCC optimize("Ofast")
#include<iostream>
using namespace std;

#define ll long long
int r, c, n;

inline ll gcd(ll a, ll b){
	while(b){ a %= b, a ^= b, b ^= a, a ^= b;}
	return a;
}

/* 1D Segment Tree */
class seg1d{
private:
	int l, r;
	ll val;
	seg1d *lc, *rc;
public:
	seg1d(int L, int R):
		l(L), r(R){
		val = 0;
		lc = rc = NULL;
	}
	inline void ensure(seg1d *& t, int p, int L, int R);
	inline void modify(int p, ll v);
	inline ll query(int L, int R);
	inline seg1d* copy();
};
// 補上父節點
inline void seg1d::ensure(seg1d *& t, int p, int L, int R){
	if(t == NULL) t = new seg1d(p, p);
	else if(p < t->l or t->r < p){
		seg1d *tmp = new seg1d(L, R);
		int M = (L + R) / 2;
		if(t->r <= M) tmp->lc = t;
		else tmp->rc = t;
		tmp->val = t->val;
		t = tmp;
	}
}
inline void seg1d::modify(int p, ll v){
	if(l == p and r == p){ val = v; return;}
	int m = (l + r) / 2;
	if(p <= m){
		ensure(lc, p, l, m);
		lc->modify(p, v);
	} else {
		ensure(rc, p, m+1, r);
		rc->modify(p, v);
	}
	val = gcd((lc ? lc->val : 0), (rc ? rc->val : 0));
}
inline ll seg1d::query(int L, int R){
	if(r < L or R < l) return 0;
	if(L <= l and r <= R) return val;
	return gcd((lc ? lc->query(L, R) : 0), (rc ? rc->query(L, R) : 0));
}
inline seg1d* seg1d::copy(){
	seg1d *tmp = new seg1d(l, r);
	tmp->val = val;
	if(lc) tmp->lc = lc->copy();
	if(rc) tmp->rc = rc->copy();
	return tmp;
}
/* 1D Segment Tree */

/* 2D Segment Tree */
class seg2d{
private:
	int u, d, l, r; // []
	seg1d val;
	seg2d *lc, *rc;
public:
	seg2d(int U, int D, int L, int R):
		u(U), d(D), l(L), r(R), val(l, r){
		lc = rc = NULL;
	}
	inline void ensure(seg2d *& t, int p, int U, int D);
	inline void modify(int x, int y, ll v);
	inline ll query(int U, int D, int L, int R);
};
inline void seg2d::ensure(seg2d *& t, int p, int U, int D){
	if(t == NULL){ t = new seg2d(p, p, l, r); return;}
	if(p < t->u or t->d < p){
		seg2d *tmp = new seg2d(U, D, l, r);
		int M = (U + D) / 2;
		if(t->d <= M) tmp->lc = t;
		else tmp->rc = t;
		tmp->val = *(t->val.copy());
		t = tmp;
	}
}
inline void seg2d::modify(int x, int y, ll v){
	if(u == x and d == x){ val.modify(y, v); return;}
	int m = (u + d) / 2;
	if(x <= m){
		ensure(lc, x, u, m);
		lc->modify(x, y, v);
	} else {
		ensure(rc, x, m+1, d);
		rc->modify(x, y, v);
	}
	val.modify(y, gcd(
		(lc ? lc->val.query(y, y) : 0),
		(rc ? rc->val.query(y, y) : 0)
	));
}
inline ll seg2d::query(int U, int D, int L, int R){
	if(d < U or D < u) return 0;
	if(U <= u and d <= D) return val.query(L, R);
	return gcd(
		lc ? lc->query(U, D, L, R): 0,
		rc ? rc->query(U, D, L, R): 0
	);
}
/* 2D Segment Tree */


int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> r >> c >> n;

	seg2d eek(0, r-1, 0, c-1);

	int cmd, p, q, u, v;
	ll k;

	for(; n; --n){
		cin >> cmd;
		if(cmd == 1){
			cin >> p >> q >> k;
			eek.modify(p, q, k);
		} else {
			cin >> p >> u >> q >> v;
			cout << eek.query(p, q, u, v) << '\n';
		}
	}
	return 0;
}