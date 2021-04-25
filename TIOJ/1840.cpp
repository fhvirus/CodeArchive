//Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

#define pb emplace_back
#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOO(i,a,b) for(int i = a; i <= b; ++i)
#define AI(x) x.begin(),x.end()

const int N = 5e4+5, M = 1e4+5;
struct QUERY{
	int l, r, k, ans;
	QUERY(int l = 0, int r = 0, int k = 0, int ans = 0):
		l(l), r(r), k(k), ans(ans){}
	// l == -1 7122
	// l == -2 add k
	// l == -3 remove k
} q[N + M * 2];
int cnt = 0;
struct BIT{
	int val[N];
	void clear(){ memset(val, 0, sizeof(val));}
	void modify(int p, int v){
		for(; p < N; p += p & -p) val[p] += v;
	}
	int query(int p){
		int ans = 0;
		for(; p > 0; p -= p & -p) ans += val[p];
		return ans;
	}
	int query(int l, int r){
		return query(r) - query(l - 1);
	}
} bit;

void tbs(int l, int r, vector<int> &qs){
	if(qs.empty()) return;
	if(l == r){
		for(int i: qs) q[i].ans = l;
		return;
	}

	int m = (l + r) / 2;
	vector<int> ql, qr;

	// update
	for(int i: qs){
		if(q[i].l == -2 and q[i].k <= m) bit.modify(q[i].r, 1);
		if(q[i].l == -3 and q[i].k <= m) bit.modify(q[i].r, -1);
		if(q[i].l > 0) q[i].ans = bit.query(q[i].l, q[i].r);
	}
	// split
	for(int i: qs){
		if(q[i].l < 0){
			if(q[i].k <= m) ql.pb(i);
			else qr.pb(i);
		} else {
			if(q[i].ans >= q[i].k) ql.pb(i);
			else qr.pb(i), q[i].k -= q[i].ans;
		}
	}
	// rollback
	for(int i: ql){
		if(q[i].l == -2 and q[i].k <= m) bit.modify(q[i].r, -1);
		if(q[i].l == -3 and q[i].k <= m) bit.modify(q[i].r, 1);
	}

	tbs(l, m, ql);
	tbs(m+1, r, qr);
}

void solve(){
	int n = R(), m = R();
	bit.clear();
	cnt = 0;
	vector<int> des;
	vector<int> a(n + 1);
	FOO(i,1,n){
		a[i] = R();
		q[cnt++] = QUERY(-2, i, a[i], 0);
		des.pb(a[i]);
	}
	for(int cmd, l, r, k; m; --m){
		cmd = R();
		if(cmd == 1){
			l = R(), r = R(), k = R();
			q[cnt++] = QUERY(l, r, k, 0);
		} else if(cmd == 2){
			r = R(), k = R();
			q[cnt++] = QUERY(-3, r, a[r], 0);
			q[cnt++] = QUERY(-2, r, k, 0);
			des.pb(a[r] = k);
		} else {
			R(); R();
			q[cnt++] = QUERY(-1, 0, 0, 7122);
		}
	}

	sort(AI(des));
	des.erase(unique(AI(des)), des.end());

	vector<int> qs;
	FOR(i,cnt){
		if(q[i].l == -1) continue;
		qs.pb(i);
		if(q[i].l > 0) continue;
		q[i].k = lower_bound(AI(des), q[i].k) - des.begin();
	}

	tbs(0, des.size() - 1, qs);

	FOR(i,cnt){
		if(q[i].l == -1) W(7122);
		else if(q[i].l > 0) W(des[q[i].ans]);
	}
}

int main(){
	for(int t = R(); t; --t) solve();
	write(1,OB,OP);
	return 0;
}
