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

signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int N, M; cin >> N >> M;
	vector<vector<pii>> adj(N + 1);
	for (int a, b, d, i = 0; i < M; ++i) {
		cin >> a >> b >> d;
		adj[b].pb(a, d);
	}

	vector<int> dis(N + 1, 1'000'000);
	queue<int> q;
	vector<bool> inq(N + 1, false);
	vector<int> upd(N + 1, 0);
	for (int i = 1; i <= N; ++i)
		q.push(i);

	while (!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = false;
		for (auto &[v, w]: adj[u]) {
			if (dis[v] <= dis[u] - w) continue;
			dis[v] = dis[u] - w;
			if (!inq[v]) {
				inq[v] = true;
				q.push(v);
				++upd[v];
				if (upd[v] > N) {
					cout << -1 << '\n';
					exit(0);
				}
			}
		}
	}

	for (int i = 1; i <= N; ++i)
		cout << dis[i] << '\n';

	return 0;
}
