// This solution is not recommended
// for it has to do some constant optimization to past the tests.
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n,char e){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}

// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
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

const int kN = 100001;
namespace SGT {
	int N;
	struct Node {
		ll val, sum; int tag;
		Node () : val(0ll), sum(0ll), tag(0) {}
	} nds[kN * 2];
	[[ gnu::pure ]] int id(int l, int r) { return (l + r) | (l != r); }
	void dfs(int l, int r, vector<int> &v) {
		int i = id(l, r);
		if (l == r) {
			nds[i].val = v[l];
			return;
		}
		int m = (l + r) / 2;
		dfs(l, m, v);
		dfs(m+1, r, v);
		nds[i].val = nds[id(l, m)].val + nds[id(m+1, r)].val;
	}
	void init(int _N, vector<int> &v) {
		N = _N;
		dfs(0, N-1, v);
	}
	inline void upd(int i, ll v) {
		nds[i].sum += nds[i].val * v;
		nds[i].tag += v;
	}
	inline void push(int i, int l, int r, int m) {
		if (nds[i].tag == 0) return;
		upd(id(l, m), nds[i].tag);
		upd(id(m+1, r), nds[i].tag);
		nds[i].tag = 0;
	}
	inline void pull(int i, int l, int r, int m) {
		nds[i].sum = nds[id(l, m)].sum + nds[id(m+1, r)].sum;
	}
	void modify(int l, int r, int ql, int qr) {
		int i = id(l, r);
		if (ql <= l and r <= qr) {
			upd(i, 1);
			return;
		}
		int m = (l + r) / 2;
		push(i, l, r, m);
		if (ql <= m) modify(l, m, ql, qr);
		if (m < qr) modify(m+1, r, ql, qr);
		pull(i, l, r, m);
	}
	ll query(int l, int r, int ql, int qr) {
		int i = id(l, r);
		if (ql <= l and r <= qr)
			return nds[i].sum;
		int m = (l + r) / 2;
		push(i, l, r, m);
		return (ql <= m ? query(l, m, ql, qr) : 0) +
			(m < qr ? query(m+1, r, ql, qr) : 0);
	}
}
namespace HLD {
	int N;
	vector<pii> adj[kN];
	int siz[kN], par[kN], top[kN];
	ll dep[kN];
	int in[kN], tot;
	ll sum, cnt;
	void dfs_sz(int u) {
		siz[u] = 1;
		for (auto &[v, w]: adj[u]) {
			dep[v] = dep[u] + w;
			dfs_sz(v);
			siz[u] += siz[v];
			if (siz[v] > siz[adj[u][0].ff]) {
				swap(v, adj[u][0].ff);
				swap(w, adj[u][0].ss);
			}
		}
	}
	void dfs_hld(int u) {
		in[u] = tot++;
		for (auto &[v, w]: adj[u]) {
			top[v] = (v == adj[u][0].ff ? top[u] : v);
			dfs_hld(v);
		}
	}
	void init(int _N) {
		N = _N;
		for (int a, b, l, i = 1; i < N; ++i) {
			a = R(); b = R(); l = R();
			adj[a].pb(b, l);
			par[b] = a;
		}
		dfs_sz(0);
		dfs_hld(0);
		vector<int> val(N, 0);
		for (int i = 0; i < N; ++i)
			for (auto &[v, w]: adj[i])
				val[in[v]] = w;
		SGT::init(N, val);
	}
	void update(int u) {
		++cnt; sum += dep[u];
		for (; u != 0; u = par[top[u]])
			SGT::modify(0, N-1, in[top[u]], in[u]);
	}
	ll query(int u) {
		ll ans = cnt * dep[u] + sum;
		for (; u != 0; u = par[top[u]])
			ans -= 2ll * SGT::query(0, N-1, in[top[u]], in[u]);
		return ans;
	}
}

signed main() {

	int N, Q; N = R(); Q = R();
	HLD::init(N);

	vector<bool> has(N, false);
	for (int t, a, i = 0; i < Q; ++i) {
		t = R(); a = R();
		if (t == 1) {
			if (has[a]) continue;
			has[a] = true;
			HLD::update(a);
		} else
			W(HLD::query(a), '\n');
	}

	write(1, OB, OP);
	return 0;
}

