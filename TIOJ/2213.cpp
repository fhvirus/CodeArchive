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

const int kN = 50005;
const ll INF = 1e18;
const int kB = 128;
const int kC = 5e7;

struct Line {
	ll m, k;
	Line (ll m = 0, ll k = 0): m(m), k(k) {}
	const ll operator () (ll x) { return m * x + k; };
};
struct LiChao {
	struct Node {
		Line line;
		int lc, rc;
		Node(ll m = 0, ll k = 0): line(m, k), lc(-1), rc(-1) {}
	};
	vector<Node> nds; int pos;
	int newNode(ll m = 0, ll k = 0){
		nds[pos++] = Node(m, k);
		return pos-1;
	}
	int n, rt;
	LiChao () {}
	void init(int nn, int sz){
		n = nn; rt = -1;
		nds.resize(sz+1);
		pos = 0;
	}
	void insert(int &nd, int l, int r, Line line){
		if(nd == -1){
			nd = newNode(line.m, line.k);
			return;
		}
		if(l == r){
			if(nds[nd].line(l-kC) < line(l-kC)) nds[nd].line = line;
			return;
		}
		int m = (l + r) / 2;
		if(nds[nd].line(m-kC) < line(m-kC)) swap(nds[nd].line, line);
		if(line.m < nds[nd].line.m) insert(nds[nd].lc, l, m, line);
		else insert(nds[nd].rc, m+1, r, line);
	}
	ll query(int nd, int l, int r, int p){
		if(nd == -1) return -INF;
		if(l == r) return nds[nd].line(p-kC);
		int m = (l + r) / 2;
		return max(nds[nd].line(p-kC), p <= m ?
				query(nds[nd].lc, l, m, p) :
				query(nds[nd].rc, m+1, r, p));
	}
	void insert(Line line){ insert(rt, 0, n, line); }
	ll query(int p){ return query(rt, 0, n, p+kC); }
} lichao;

int n, m, a[kN], lim[kN];
ll pre[kN], dp0[kN], dp1[kN];
Line sc[kN];

void go(ll dp[kN], int l, int r){
	// Brute force if range small enough
	if(r - l + 1 <= kB){
		for(int i = l; i <= r; ++i){
			ll cst = pre[i] * (pre[n]-pre[i]);
			for(int j = max(l==1?0:l, lim[i]); j < i; ++j)
				dp[i] = max(dp[i], sc[j](pre[i]) + cst);
			sc[i] = Line(2 * pre[i], max(-INF, dp[i] - pre[i] * (pre[i] + pre[n])));
		}
		return;
	}

	// Some kind of DQ
	int m = (l+r) / 2;
	go(dp, l, m);
	lichao.init(2 * kC, m-l+1);
	for(int i = r, j = m; i > m; --i){
		if(lim[i] > m) continue;
		while(j >= (l==1?0:l) and j >= lim[i]){
			lichao.insert(sc[j]);
			--j;
		}
		ll cst = pre[i] * (pre[n]-pre[i]);
		dp[i] = max(dp[i], lichao.query(pre[i]) + cst);
		sc[i] = Line(2 * pre[i], max(-INF, dp[i] - pre[i] * (pre[i] + pre[n])));
	}
	go(dp, m, r);
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	for(int i = 0; i <= n; ++i) lim[i] = 0;
	for(int u, v, i = 0; i < m; ++i){
		cin >> u >> v;
		lim[v] = max(lim[v], u);
	}
	for(int i = 1; i <= n; ++i) pre[i] = a[i] + pre[i-1];
	for(int i = 1; i <= n; ++i) lim[i] = max(lim[i], lim[i-1]);

	dp0[0] = 0; sc[0] = Line(0, 0);
	for(int i = 1; i <= n; ++i) dp0[i] = -INF;
	go(dp0, 1, n);

	dp1[0] = -INF; sc[0] = Line(0, -INF);
	for(int i = 1; i <= n; ++i) dp1[i] = dp0[i-1] + a[i] * (pre[n]-a[i]);
	go(dp1, 1, n);

	cout << dp1[n] / 2 << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t; cin >> t;
	for(; t; --t) solve();
	return 0;
}
