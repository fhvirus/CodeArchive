#pragma GCC optimize("Ofast")
#include<unistd.h>
#define ll long long
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline ll RL(){static char c;ll a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(ll n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}
inline ll gcd(ll a, ll b){ while(b){ a %= b, b ^= a, a ^= b, b ^= a;} return a;}

const int N = 2e6;
/* 1D Segment Tree */
class seg1d{
private:
	int l, r;
	ll val;
	seg1d *lc, *rc;
public:
	seg1d(){ val = 0, lc = rc = NULL;}
	seg1d(int L, int R):
		l(L), r(R){
		val = 0;
		lc = rc = NULL;
	}
	inline void ensure(seg1d *& t, int p, int L, int R);
	inline void modify(int p, ll v);
	inline ll query(int L, int R);
	inline seg1d* copy();
} node1d[N];
inline seg1d* newNode1d(int L, int R){
	static int cnt = 0;
	node1d[cnt] = seg1d(L, R);
	return &node1d[cnt++];
}
// 補上父節點
inline void seg1d::ensure(seg1d *& t, int p, int L, int R){
	if(t == NULL) t = newNode1d(p, p);
	else if(p < t->l or t->r < p){
		seg1d *tmp = newNode1d(L, R);
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
	seg1d *tmp = newNode1d(l, r);
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
	int r, c, n;
	r = R(), c = R(), n = R();

	seg2d eek(0, r-1, 0, c-1);

	for(int cmd; n; --n){
		cmd = R();
		if(cmd == 1){
			int x, y; ll k;
			x = R(), y = R(), k = RL();
			eek.modify(x, y, k);
		} else {
			int u, d, l, r;
			u = R(), l = R(), d = R(), r = R();
			W(eek.query(u, d, l, r));
		}
	}
	write(1,OB,OP);
	return 0;
}