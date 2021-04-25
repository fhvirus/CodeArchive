// Knapsack DP is harder than FFT.
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}
inline char RR(){ static char c; while((c = RC()) != 'N' and c != 'D'); return c;}

#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define AI(x) (x).begin(),(x).end()

const int N = 5e5 + 225;
int ccc;
int siz[N], par[N];
vector<tuple<int, int, int, int>> mod;
void init(int n){
	ccc = n;
	fill(siz, siz + n, 1);
	iota(par, par + n, 0);
	mod.clear();
}
inline int find(int a){
	while(a != par[a])
		a = par[a];
	return a;
}
inline bool onion(int a, int b){
	a = find(a);
	b = find(b);
	if(a == b) return false;
	if(siz[a] < siz[b]) swap(a, b);

	mod.pb(a, siz[a], b, par[b]);

	--ccc;
	siz[a] += siz[b];
	par[b] = a;
	return true;
}
inline void undo(){
	auto [p, ps, q, qp] = mod.back(); mod.pop_back();
	siz[p] = ps;
	par[q] = qp;
	++ccc;
}

int ans[N];
vector<pii> nd[N * 4];
void insertEvent(int p, int l, int r, int ql, int qr, pii v){
	if(ql <= l and r <= qr){
		nd[p].push_back(v);
		return;
	}
	int m = (l + r) / 2;
	if(qr <= m){
		insertEvent(p * 2, l, m, ql, qr, v);
	} else if(ql > m){
		insertEvent(p * 2 + 1, m+1, r, ql, qr, v);
	} else {
		insertEvent(p * 2, l, m, ql, qr, v);
		insertEvent(p * 2 + 1, m+1, r, ql, qr, v);
	}
}
void traverse(int p, int l, int r){
	int cnt = 0;
	for(auto i: nd[p]){
		if(onion(i.ff, i.ss))
			++cnt;
	}
	if(l == r){
		ans[l] = ccc;
	} else {
		int m = (l + r) / 2;
		traverse(p * 2, l, m);
		traverse(p * 2 + 1, m + 1, r);
	}
	for(; cnt; --cnt) undo();
	nd[p].clear();
}


struct pair_hash {
    size_t operator ()(const pair<int,int> &p) const{
        return hash<ll>()(((ll)p.first*N + p.second));
    }
};
gp_hash_table<pair<int,int>,pair<int,int>,pair_hash> mp;

inline void addEdge(int a, int b, int t){
	if(a > b) swap(a, b);
	pii e(a, b);
	if(mp.find(e) == end(mp) or mp[e].ss == 0)
		mp[e] = {t, 1};
	else
		mp[e].ss++;
}
inline void remEdge(int a, int b, int t, int q){
	if(a > b) swap(a, b);
	pii e(a, b);
	assert(mp.find(e) != mp.end() and mp[e].ss != 0);
	mp[e].ss--;
	if(mp[e].ss == 0)
		insertEvent(1, 0, q, mp[e].ff, t - 1, e);
}

void solve(){
	int n, m, q;
	mp.clear();
	
	n = R(), m = R(), q = R();
	vector<tuple<char, int, int, int>> qs;
	for(int a, b; m; --m){
		a = R(), b = R();
		qs.pb('N', a, b, 0);
	}
	FOO(t, 1, q){
		char c; int a, b;
		c = RR(), a = R(), b = R();
		qs.pb(c, a, b, t);
	}
	for(auto [c, a, b, t]: qs){
		if(c == 'N') addEdge(a, b, t);
		else remEdge(a, b, t, q);
	}
	for(auto i: mp){
		auto [e, f] = i;
		if(f.ss != 0) insertEvent(1, 0, q, f.ff, q, e);
	}
	init(n);
	traverse(1, 0, q);
	FOO(i,1,q) W(ans[i]);
}

int32_t main(){
	for(int t = R(); t; --t) solve();
	write(1,OB,OP);
	return 0;
}

