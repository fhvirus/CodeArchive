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

const int kN = 100001;
const int kC = 1000004;
inline unsigned rnd() {
	static unsigned x = 131;
	return ++(x *= 0xdefaced);
}

struct DS {
	static const int kNode = 200002;
	struct Node {
		int key, val, tag, sum;
		unsigned pri;
		int lc, rc;
		Node () {}
		Node (int k, int v) :
			key(k), val(v), tag(0), sum(v),
			pri(rnd()), lc(0), rc(0) {}
	} nds[kNode];
	int newNode(int k, int v) {
		static int tot = 0;
		nds[++tot] = Node(k, v);
		return tot;
	}
	void upd(int u, int v) {
		if (u != 0) {
			nds[u].key += v;
			nds[u].tag += v;
		}
	}
	void push(int u) {
		upd(nds[u].lc, nds[u].tag);
		upd(nds[u].rc, nds[u].tag);
		nds[u].tag = 0;
	}
	void pull(int u) {
		Node &nd = nds[u];
		nd.sum = nd.val + nds[nd.lc].sum + nds[nd.rc].sum;
	}
	int merge(int u, int v) {
		if (!u) return v;
		if (!v) return u;
		if (nds[u].pri > nds[v].pri) {
			push(u);
			nds[u].rc = merge(nds[u].rc, v);
			pull(u);
			return u;
		} else {
			push(v);
			nds[v].lc = merge(u, nds[v].lc);
			pull(v);
			return v;
		}
	}
	void splitByKey(int o, int k, int &u, int &v) {
		if (!o) {
			u = v = 0;
			return;
		}
		push(o);
		if (nds[o].key <= k) {
			u = o;
			splitByKey(nds[o].rc, k, nds[u].rc, v);
			pull(u);
		} else {
			v = o;
			splitByKey(nds[o].lc, k, u, nds[v].lc);
			pull(v);
		}
	}
	int findKth(int u, int k) {
		push(u);
		int lsz = nds[nds[u].lc].sum;
		if (lsz >= k)
			return findKth(nds[u].lc, k);
		if (lsz + nds[u].val < k)
			return findKth(nds[u].rc, k - nds[u].val - lsz);
		return nds[u].key;
	}

	// now the main part
	int root;
	DS (): root(0) {}
	void insert(int k, int v) {
		debug("insert", k, v);
		int a, b, c, d;
		splitByKey(root, k-1, a, b);
		splitByKey(b, k, c, d);
		debug(a, c, d);
		if (!c) c = newNode(k, v);
		else {
			nds[c].val += v;
			nds[c].sum += v;
		}
		root = merge(a, merge(c, d));
	}
	void insert(int &u, int k, int v) {
		debug("insert2", k, v);
		int a, b, c, d;
		splitByKey(u, k-1, a, b);
		splitByKey(b, k, c, d);
		if (!c) c = newNode(k, v);
		else {
			nds[c].val += v;
			nds[c].sum += v;
		}
		u = merge(a, merge(c, d));
	}
	void add1(int x) {
		debug("add1", x);
		int k = findKth(root, x);
		int a, b, c, d;
		splitByKey(root, k-1, a, b);
		splitByKey(b, k, c, d);
		upd(a, 1);
		x -= nds[a].sum;
		int y = nds[c].val - x;
		debug(k, x, y);
		if (x) insert(d, k+1, x);
		if (y) insert(a, k, y);
		root = merge(a, d);
	}
	int getMax() {
		int u = root;
		while (nds[u].rc != 0)
			u = nds[u].rc;
		return nds[u].key;
	}
	void dfs(int u) {
		if (!u) return;
		Node &nd = nds[u];
		dfs(nd.lc);
		debug(u, nd.lc, nd.rc, nd.key, nd.val, nd.sum);
		dfs(nd.rc);
	}
	void de() { dfs(root); }
};

int n, m, sum[kC], rb;
vector<int> wok[kC];

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	cin >> n;
	for (int s, e, i = 0; i < n; ++i) {
		cin >> s >> e;
		++sum[s]; --sum[e+1];
		rb = max(rb, e);
	}

	cin >> m;
	for (int w, d, i = 0; i < m; ++i) {
		cin >> w >> d;
		wok[d].pb(w);
		rb = max(rb, d);
	}

	DS ds;
	for (int i = 1; i <= rb; ++i) {
		sum[i] += sum[i-1];
		ds.insert(sum[i], 1);
		//ds.de();
		for (int w: wok[i])
			ds.add1(w);
		debug(i);
		//ds.de();
	}
	cout << ds.getMax() << '\n';
	return 0;
}
