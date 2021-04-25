// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';write(1,OB,OP);}

#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define OOF(i,a,b) for(int i=(a);i>=int(b);--i)
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
template<class T> using minheap = 
	priority_queue<T, vector<T>, greater<T>>;

const ll INF = 4e18;
const int N = 3e5 + 225;
int n, m, s, t;
int P[N], Pid[N], Ps;
vector<int> F, G;
vector<ll> FD, GD;
vector<ll> noF, noG;
minheap<pair<ll, int>> pq;
minheap<tuple<ll, int, int>> pqq;
// int F[N], G[N];
// ll FD[N], GD[N];

struct Edge{
	int v; ll w;
	Edge(int v = 0, ll w = 0):
		v(v), w(w){}
};
vector<Edge> adj[N];
struct SegmentTree{
	int n;
	ll val[N * 2];
	void init(int _n){
		n = _n;
		fill(val, val + n * 2, INF);
	}
	void update(int l, int r, ll v){
		++r;
		for(l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l & 1) chmin(val[l], v), ++l;
			if(r & 1) --r, chmin(val[r], v);
		}
	}
	ll query(int p){
		ll ans = INF;
		for(p += n; p > 0; p >>= 1){
			chmin(ans, val[p]);
		}
		return ans;
	}
} sgt;

void dfs(int u, int fx, vector<int> &f, vector<ll> &dis){
	for(auto [v, w]: adj[u]){
		if(f[v] == -1 and dis[u] + w == dis[v]){
			f[v] = fx;
			dfs(v, fx, f, dis);
		}
	}
}
void findF(int s, int t, vector<int> &F, vector<ll> &dis, bool noP){
	if(!noP){
		dis[s] = 0; pq.emplace(dis[s], s);
		while(!pq.empty()){
			auto [d, u] = pq.top(); pq.pop();
			if(dis[u] < d) continue;
			for(auto [v, w]: adj[u]){
				if(chmin(dis[v], d + w)){
					pq.emplace(dis[v], v);
				}
			}
		}
	} else {
		vector<int> sc(n + 1, -1);

		dis[s] = 0; pq.emplace(dis[s], s);
		while(!pq.empty()){
			auto [d, u] = pq.top(); pq.pop();
			if(dis[u] < d) continue;
			for(auto [v, w]: adj[u]){
				if(chmin(dis[v], d + w)){
					pq.emplace(dis[v], v);
					sc[v] = u;
				}
			}
		}
		for(int u = t; ; u = sc[u]){
			P[Ps++] = u;
			if(u == s) break;
		}
		reverse(P, P + Ps);

		fill(Pid, Pid + n + 1, -1);
		FOR(i,Ps) Pid[P[i]] = i;
	}

	FOR(i,Ps) F[P[i]] = P[i];
	FOR(i,Ps) dfs(P[i], P[i], F, dis);
}
void caseC(vector<int> &F, vector<ll> &FD, vector<ll> &noF, bool isG){
	noF.resize(n + 1, INF);

	// [dis, v, f[i]]
	FOO(u,1,n){
		for(auto [v, w]: adj[u]){
			if(Pid[v] != -1) continue;
			if(F[u] == F[v]) continue;
			if((Pid[F[u]] < Pid[F[v]]) ^ isG){
				if(chmin(noF[v], FD[u] + w))
					pqq.emplace(noF[v], v, F[v]);
			}
		}
	}
	while(!pqq.empty()){
		auto [d, u, fu] = pqq.top(); pqq.pop();
		if(noF[u] < d) continue;
		for(auto [v, w]: adj[u]){
			if(F[v] != fu) continue;
			if(F[v] == v) continue;
			if(chmin(noF[v], d + w))
				pqq.emplace(noF[v], v, fu);
		}
	}
}

int32_t main(){
	n = R(), m = R(), s = R(), t = R();
	FOR(_,m){
		int u, v; ll w;
		u = R(), v = R(), w = R();
		adj[u].pb(v, w);
		adj[v].pb(u, w);
	}

	F.resize(n + 1, -1);
	G.resize(n + 1, -1);
	FD.resize(n + 1, INF);
	GD.resize(n + 1, INF);

	// Find Path
	// Find F, FD
	// Find G, GD
	findF(s, t, F, FD, true);

	if(Ps == n){
		W(-1);
		return 0;
	}

	reverse(P, P + Ps);
	findF(t, s, G, GD, false);
	reverse(P, P + Ps);
	caseC(F, FD, noF, false);
	caseC(G, GD, noG, true);

	// Case S - A - B - T
	// Case S - A - T
	// Case 3
	sgt.init(Ps);
	auto update = [](int l, int r, ll v){
		l = Pid[F[l]] + 1;
		r = Pid[G[r]] - 1;
		if(l > r) return;
		sgt.update(l, r, v);
	};
	FOO(u,1,n){
		for(auto [v, w]: adj[u]){
			if(Pid[F[u]] < Pid[G[v]])
				update(u, v, FD[u] + w + GD[v]);
		}
		if(F[u] != G[u]) update(u, u, FD[u] + GD[u]);
		else{
			if(Pid[u] != -1) continue;
			sgt.update(Pid[F[u]], Pid[G[u]], noF[u] + noG[u]);
		}
	}
	
	// calc ans
	ll ans = -INF;
	int ansu = -1;
	FOO(i,1,n){
		if(Pid[i] == -1){
			if(chmax(ans, FD[t])){
				ansu = i;
				break;
			}
		}
	}
	FOR(i,Ps){
		int u = P[i];
		ll ret = sgt.query(Pid[u]);
		if(ret == INF) continue;
		if(chmax(ans, ret))
			ansu = u;
		else if(ans == ret)
			chmin(ansu, u);
	}
	if(ans == INF and Ps == n){
		W(-1), W(FD[t]);
		return 0;
	}
	W(ansu), W(ans);
	return 0;
}
