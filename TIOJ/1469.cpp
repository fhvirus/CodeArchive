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

const int kN = 111;
const int INF = 1e9 + 7;
struct DIN {
	struct E {
		int v, c, r;
		E(int v, int c, int r): v(v), c(c), r(r) {}
	};
	vector<E> adj[kN];
	void add(int u, int v, int c){
		adj[u].pb(v, c, (int) adj[v].size() );
		adj[v].pb(u, 0, (int) adj[u].size()-1 );
	}
	int n, s, t;
	void init(int nn, int ss, int tt){
		n = nn; s = ss; t = tt;
		for(int i = 0; i <= n; ++i)
			adj[i].clear();
	}
	int le[kN], it[kN];
	int bfs(){
		fill(le, le+n+1, -1); le[s] = 0;
		queue<int> q; q.push(s);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(auto [v, c, r]: adj[u]){
				if(le[v] == -1 and c > 0){
					le[v] = le[u] + 1;
					q.push(v);
				}
			}
		}
		return ~le[t];
	}
	int dfs(int u, int f){
		if(u == t) return f;
		for(int &i = it[u]; i < (int) adj[u].size(); ++i){
			auto &[v, c, r] = adj[u][i];
			if(c > 0 and le[u] + 1 == le[v]){
				int d = dfs(v, min(c, f));
				if(d > 0){
					c -= d;
					adj[v][r].c += d;
					return d;
				}
			}
		}
		return 0;
	}
	int flow(){
		int ans = 0, u;
		while(bfs()){
			fill(it, it+n+1, 0);
			while(u = dfs(s, INF))
				ans += u;
		}
		return ans;
	}
} din;

inline int siz(string s){
	if(s == "XXL") return 1;
	else if(s == "XL") return 2;
	else if(s == "L") return 3;
	else if(s == "M") return 4;
	else if(s == "S") return 5;
	else if(s == "XS") return 6;
	else assert(0);
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N, M;
	while(cin >> N >> M){
		N /= 6;
		int s = 0, t = M + 7;
		din.init(t, s, t);
		for(int i = 1; i <= 6; ++i)
			din.add(s, i, N);

		for(int i = 1; i <= M; ++i){
			din.add(i+6, t, 1);
			string in;
			for(int j = 0; j < 2; ++j){
				cin >> in;
				int id = siz(in);
				din.add(id, i+6, 1);
			}
		}
		cout << (din.flow() == M ? "YES\n" : "NO\n");
	}
	return 0;
}
