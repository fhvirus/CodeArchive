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

const int INF = 1e9 + 7;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> adj(n, vector<int>(n, INF));
	for (int u, v, w, i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		adj[u][v] = adj[v][u] = w;
	}

	int k, msk = 0, st = -1;
	cin >> k;
	for (int u, i = 0; i < k; ++i) {
		cin >> u;
		if (st == -1) st = u;
		else msk |= (1 << u);
	}

	// Floyd-Warshall
	vector<vector<int>> dis = adj;
	vector<vector<int>> prv(n, vector<int>(n, -1));
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i) if (dis[i][k] < INF)
			for (int j = 0; j < n; ++j) if (dis[k][j] < INF)
				if (dis[i][k] + dis[k][j] < dis[i][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
					prv[i][j] = k;
				}

	vector<vector<int>> dp(1 << n, vector<int>(n, INF));
	vector<vector<int>> sc(1 << n, vector<int>(n, INF));
	fill(AI(dp[0]), 0);
	fill(AI(sc[0]), -1);

	for (int s = 0; s = (s - msk) & msk; ) {
		for (int i = 0; i < n; ++i) if (!(s >> i & 1) and ((msk >> i & 1) or i == st)) {
			for (int j = 0; j < n; ++j) if (s >> j & 1) {
				// not visited s, current at i
				// next goes to j
				int t = s ^ (1 << j);
				int val = dis[i][j] + dp[t][j];
				if (dp[s][i] > val) {
					dp[s][i] = val;
					sc[s][i] = j;
				}
			}
		}
	}

	vector<int> des;
	for (int i = msk, j = st; ; ) {
		des.pb(j);
		if (sc[i][j] == -1) break;
		int u = i ^ (1 << sc[i][j]);
		int v = sc[i][j];
		i = u; j = v;
	}
	debug(des);

	cout << "Minimum travel distance: " << dp[msk][st] << '\n';
	cout << "Travel route: ";

	function<void(int, int)> printPath = [&](int u, int v) {
		if (prv[u][v] == -1) {
			cout << u << ' ';
			return;
		}
		printPath(u, prv[u][v]);
		printPath(prv[u][v], v);
	};

	for (int i = 1; i < k; ++i)
		printPath(des[i-1], des[i]);
	cout << des[k-1] << '\n';

	return 0;
}
