// Knapsack DP is harder than FFT.
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
int n, q;
struct Query{
	int t, p, x;
	Query(int t = 0, int p = 0, int x = 0):
		t(t), p(p), x(x){}
};
vector<vector<Query>> qs;
vector<int> ans;
void input(){
	n = R(), q = R();
	ans.resize(q, -1);
	qs.resize(n + 1);
	int t, l, r, x;
	FOR(i,q){
		t = R();
		if(t == 1){
			l = R(), r = R(), x = R();
			qs[l].pb(1, i, x);
			qs[r + 1].pb(1, i, -x);
		} else {
			x = R();
			qs[x].pb(2, i, i);
		}
	}
}

struct node{
	int v, c, t;
	node(): v(0), c(1), t(0){}
} nd[300003 * 4];
#define lc (p*2)
#define rc (p*2+1)
void build(int p, int l, int r){
	if(l + 1 >= r) return;
	int m = (l + r) / 2;
	build(lc, l, m);
	build(rc, m, r);
	nd[p].c = nd[lc].c + nd[rc].c;
}
void push(int p, int l, int r){
	nd[p].v += nd[p].t;
	if(l + 1 < r){
		nd[lc].t += nd[p].t;
		nd[rc].t += nd[p].t;
	}
	nd[p].t = 0;
}
void pull(int p){
	int a = lc, b = rc;
	if(nd[a].v > nd[b].v) swap(a, b);
	nd[p].v = nd[a].v;
	nd[p].c = nd[a].c;
	if(nd[a].v == nd[b].v) nd[p].c += nd[b].c;
}
void add(int p, int l, int r, int ql, int qr, int v){
	push(p, l, r);
	if(qr <= l || r <= ql) return;
	if(ql <= l && r <= qr){
		nd[p].t += v;
		push(p, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(lc, l, m, ql, qr, v);
	add(rc, m, r, ql, qr, v);
	pull(p);
}
pii merge(pii a, pii b){
	if(a.ff > b.ff) swap(a, b);
	if(a.ff == b.ff) a.ss += b.ss;
	return a;
}
pii query(int p, int l, int r, int ql, int qr){
	push(p, l, r);
	if(qr <= l || r <= ql) return {  8e7, nd[p].c};
	if(ql <= l && r <= qr) return {nd[p].v, nd[p].c};
	int m = (l + r) / 2;
	return merge(
		query(lc, l, m, ql, qr),
		query(rc, m, r, ql, qr)
	);
}
void solve(){
	build(1, 0, q);
	FOR(i,n){
		for(auto [t, p, x]: qs[i]){
			if(t == 1)
				add(1, 0, q, p, q, x);
			else{
				pii res = query(1, 0, q, 0, p);
				if(res.ff == 0) ans[x] = res.ss;
				else ans[x] = 0;
			}
		}
	}
	FOR(i,q) if(~ans[i]) W(ans[i]);
}
int32_t main(){
	input();
	solve();
	write(1,OB,OP);
	return 0;
}
