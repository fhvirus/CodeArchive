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

const int kN = 200002;
const int kL = 20;

int n, q;
bitset<kN> vis;
int stamp[kN], tot;
bitset<kN> onCycle;
int cycleID[kN];
int posOnCycle[kN];
int cycleSize[kN];
int rootVertex[kN];
int depth[kN];

int mango[kL][kN];
int *t = mango[0];

void dfs(int u) {
	vis[u] = true;
	int v = t[u];
	if (!vis[v]) dfs(v);
	cycleID[u] = cycleID[v];
	rootVertex[u] = rootVertex[v];
	depth[u] = depth[v] + 1;
	return;
}
int go(int u, int d) {
	if (d < 0) return -1;
	for (int l = kL - 1; l >= 0; --l)
		if (d >> l & 1) u = mango[l][u];
	return u;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		cin >> t[i];

	// get cycle heads
	vector<int> cycleHead;
	for (int i = 1; i <= n; ++i) {
		if (vis[i]) continue;
		++tot;
		int u = i;
		do {
			vis[u] = true;
			stamp[u] = tot;
			u = t[u];
		} while (!vis[u]);
		if (stamp[u] == tot)
			cycleHead.pb(u);
	}

	// mark cycle
	vis.reset();
	for (int i = 0; i < (int) cycleHead.size(); ++i) {
		int u = cycleHead[i];
		if (vis[u]) continue;
		int pos = 0;
		do {
			vis[u] = true;
			onCycle[u] = true;
			cycleID[u] = i+1;
			rootVertex[u] = u;
			posOnCycle[u] = pos++;
			u = t[u];
		} while (!onCycle[u]);
		cycleSize[i+1] = pos;
	}

	// mark other nodes
	for (int i = 1; i <= n; ++i) {
		if (vis[i] or onCycle[i]) continue;
		dfs(i);
	}

	for (int l = 1; l < kL; ++l)
		for (int i = 1; i <= n; ++i)
			mango[l][i] = mango[l-1][mango[l-1][i]];

	for (int a, b, i = 0; i < q; ++i) {
		cin >> a >> b;
		if (cycleID[a] != cycleID[b] or
				(onCycle[a] and !onCycle[b])) {
			cout << -1 << '\n';
			continue;
		}
		if (onCycle[a] and onCycle[b]) {
			int ans = posOnCycle[b] - posOnCycle[a];
			if (ans < 0) ans += cycleSize[cycleID[b]];
			cout << ans << '\n';
		} else if (onCycle[b]) {
			int ans = posOnCycle[b] - posOnCycle[rootVertex[a]];
			if (ans < 0) ans += cycleSize[cycleID[b]];
			ans += depth[a];
			cout << ans << '\n';
		} else {
			int d = depth[a] - depth[b];
			int c = go(a, d);
			cout << (c == b ? d : -1) << '\n';
		}
	}

	return 0;
}
