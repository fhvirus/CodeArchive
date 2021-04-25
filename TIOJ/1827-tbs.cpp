// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!=-1);a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<vector>
using namespace std;
#define pb emplace_back
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)

int n, m;

struct BIT{
	int n; int v[100001];
	void init(int _n){ n = _n; fill(v, v + n + 1, 0);}
	void modify(int p, int val){ for(; p <= n; p += p & -p) v[p] += val;}	
	int query(int p){ int r = 0; for(; p > 0; p -= p & -p) r += v[p]; return r;}
} bit;
struct query{
	int id, p, k;
	query(int _id = 0, int _p = 0, int _k = 0):
		id(_id), p(_p), k(_k){}
};

void solve(int l, int r, vector<query> & qs, vector<int> & ans){
	if(l == r){
		for(auto i: qs)
			if(i.id > n) ans[i.id - n] = l;
		return;
	}
	if(qs.empty() or qs.back().id <= n) return;
	int m = (l + r) / 2;
	vector<query> ql, qr;
	// do something
	int i = 0;
	for(; qs[i].id <= n; ++i){
		auto q = qs[i];
		if(q.p <= m) bit.modify(q.id, 1), ql.push_back(q);
		else qr.push_back(q);
	}
	for(; i < qs.size(); ++i){
		auto q = qs[i];
		int cur = bit.query(min(n, q.p + m)) - bit.query(max(1, q.p - m) - 1);
		if(cur >= q.k) ql.push_back(q);
		else qr.push_back(q);
	}
	solve(m+1, r, qr, ans);
	// undo something
	for(auto q: ql){
		if(q.id > n) break;
		bit.modify(q.id, -1);
	}
	solve(l, m, ql, ans);
}


int main(){
	n = R(); m = R();
	bit.init(n);
	vector<query> qs;
	FOO(i,1,n) qs.push_back({i, R(), 0});
	FOO(i,1,m) qs.push_back({i + n, R() + 1, R()});
	vector<int> ans(m + 1);
	solve(1, n, qs, ans);
	FOO(i,1,m) W(ans[i]);
	write(1,OB,OP);
	return 0;
}