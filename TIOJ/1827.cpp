// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)

const int N = 1e5 + 225, M = 1e9 + 7;
int n, a[N], m;

struct node{
	int val;
	node *lc, *rc;
	node(int v = 0): val(v), lc(NULL), rc(NULL){}
	void pull(){ val = lc->val + rc->val;}
};
node* foo(node* nd){
	node* nn = new node();
	nn->val = nd->val;
	nn->lc = nd->lc;
	nn->rc = nd->rc;
	return nn;
}
node* build(int l, int r){
	if(l == r) return new node();
	int m = (l + r) / 2;
	node* nd = new node();
	nd->lc = build(l, m);
	nd->rc = build(m+1, r);
	return nd;
}
void modify(node* old, node* nd, int l, int r, int p, int v){
	if(l == r){
		assert(p == l);
		nd->val += v;
		return;
	}
	int m  = (l + r) / 2;
	if(p <= m){
		nd->lc = foo(old->lc);
		modify(old->lc, nd->lc, l, m, p, v);
	} else {
		nd->rc = foo(old->rc);
		modify(old->rc, nd->rc, m+1, r, p, v);
	}
	nd->pull();
}
int query(node* nd, int l, int r, int ql, int qr){
	if(qr < l or r < ql) return 0;
	if(ql <= l and r <= qr) return nd->val;
	int m = (l + r) / 2;
	return query(nd->lc, l, m, ql, qr) + query(nd->rc, m+1, r, ql, qr);
}
node* rt[N];
int taimu = 0;

bool check(int p, int k, int s){
	++p;
	int l = max(1, p - s), r = min(n, p + s);
	return query(rt[r], 1, n, 1, s) - query(rt[l-1], 1, n, 1, s) >= k;
}

int solve(int p, int k){
	int l = n, x = __lg(n);
	for(; x >= 0; --x) if(l >= (1<<x) and check(p, k, l - (1<<x))) l -= (1<<x);
	return l;
}

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m;
	FOO(i,1,n) cin >> a[i];

	rt[taimu++] = build(1, n);
	FOO(i,1,n){
		rt[taimu] = foo( rt[taimu-1] );
		modify(rt[taimu-1], rt[taimu], 1, n, a[i], 1);
		++taimu;
	}
	
	for(int p, k; m; --m){
		cin >> p >> k;
		cout << solve(p, k) << '\n';
	}
	return 0;
}

