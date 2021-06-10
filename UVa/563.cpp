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

const int N = 5005, INF = INT_MAX;
struct DIN{
	struct E{
		int v, c, r;
		E(int v, int c, int r):
			v(v), c(c), r(r){}
	};
	vector<E> adj[N];
	void add(int u, int v, int c){
		adj[u].pb(v, c, (int) adj[v].size());
		adj[v].pb(u, 0, (int) adj[u].size() - 1);
	}
	int n, s, t;
	void init(int nn, int ss, int tt){
		n = nn, s = ss, t = tt;
		for(int i = 0; i <= n; ++i)
			adj[i].clear();
	}
	int le[N], it[N];
	void bfs(){
		fill(le, le + N, -1); le[s] = 0;
		queue<int> q; q.push(s);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(auto [v, c, r]: adj[u]){
				if(c > 0 and le[v] == -1)
					le[v] = le[u] + 1, q.push(v);
			}
		}
	}
	int dfs(int u, int f){
		if(u == t) return f;
		for(int &i = it[u]; i < (int) adj[u].size(); ++i){
			auto &[v, c, r] = adj[u][i];
			if(c > 0 and le[v] == le[u] + 1){
				int ans = dfs(v, min(c, f));
				if(ans > 0){
					c -= ans;
					adj[v][r].c += ans;
					return ans;
				}
			}
		}
		return 0;
	}
	int flow(){
		int ans = 0, u;
		while(1){
			bfs(); if(le[t] == -1) break;
			fill(it, it + N, 0);
			while((u = dfs(s, INF)) > 0) ans += u;
		}
		return ans;
	}
} din;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int n, m, r;
int id(int x, int y, bool b){
	return (x - 1) * m + y + (b ? n * m : 0);
}

void solve(){
	cin >> n >> m >> r;
	int s = 0, t = n * m * 2 + 1;
	din.init(t, s, t);

	for(int x, y, i = 0; i < r; ++i){
		cin >> x >> y;
		din.add(s, id(x, y, 0), 1);
	}
	for(int x = 1; x <= n; ++x){
		for(int y = 1; y <= m; ++y){
			for(int d = 0; d < 4; ++d){
				int nx = x + dx[d], ny = y + dy[d];
				if(nx < 1 or nx > n or ny < 1 or ny > m) continue;
				din.add(id(x, y, 1), id(nx, ny, 0), 1);
			}
			din.add(id(x, y, 0), id(x, y, 1), 1);
		}
	}

	for(int x = 1; x <= n; ++x){
		din.add(id(x, 1, 1), t, 1);
		din.add(id(x, m, 1), t, 1);
	}
	for(int y = 2; y < n; ++y){
		din.add(id(1, y, 1), t, 1);
		din.add(id(n, y, 1), t, 1);
	}

	if(din.flow() == r) cout << "possible\n";
	else cout << "not possible\n";
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t; cin >> t;
	for(; t; --t) solve();
	return 0;
}
