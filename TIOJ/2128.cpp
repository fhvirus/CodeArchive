// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i = 0; i < (n); ++i)
#define FOO(i,a,b) for(int i = (a); i <= (b); ++i)
#define AI(x) (x).begin(),(x).end()
template<typename I> bool chmax(I &a, I b){ return a < b ? (a = b, true) : false;}
template<typename I> bool chmin(I &a, I b){ return b < a ? (a = b, true) : false;}

#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(ll n, char e){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}

struct Dinic{
	static const int N = 4004;
	static const int INF = 1000000007;
	struct Edge{
		int to, cap, rev;
		Edge(){}
		Edge(int t, int c, int r):
			to(t), cap(c), rev(r){}
	};
	vector<Edge> G[N];
	inline void addEdge(int from, int to, int cap){
		G[from].pb(to, cap, (int) G[to].size());
		G[to].pb(from, 0, (int)G[from].size() - 1);
	}
	int n, s, t;
	void init(int _n, int _s, int _t){
		n = _n, s = _s, t = _t;
		FOO(i,0,n) G[i].clear();
	}
	int level[N], iter[N];
	void bfs(){
		memset(level, -1, sizeof(level));
		level[s] = 0;
		queue<int> q; q.push(s);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(Edge e: G[u]){
				if(e.cap > 0 and level[e.to] == -1){
					level[e.to] = level[u] + 1;
					q.push(e.to);
				}
			}
		}
	}
	int dfs(int u, int flow){
		if(u == t) return flow;
		for(int &i = iter[u]; i < (int) G[u].size(); ++i){
			Edge &e = G[u][i];
			if(e.cap > 0 and level[e.to] == level[u] + 1){
				int ret = dfs(e.to, min(flow, e.cap));
				if(ret > 0){
					e.cap -= ret;
					G[e.to][e.rev].cap += ret;
					return ret;
				}
			}
		}
		return 0;
	}
	ll flow(){
		ll ret = 0;
		while(true){
			bfs();
			if(level[t] == -1) break;
			memset(iter, 0, sizeof(iter));
			int u;
			while((u = dfs(s, INF)) > 0){
				ret += u;
			}
		}
		return ret;
	}
	bool vis[N];
	vector<int> scut(){
		memset(vis, false, sizeof(vis));
		queue<int> q;
		q.push(0);
		vector<int> ans;
		while(!q.empty()){
			int u = q.front(); q.pop();
			if(vis[u]) continue;
			vis[u] = true;
			ans.pb(u);
			for(Edge e: G[u]){
				if(e.cap > 0 and !vis[e.to])
					q.push(e.to);
			}
		}
		return ans;
	}
} dinic;
int32_t main(){
	int t, n, m;
	for(t = R(); t; --t){
		n = R(), m = R();
		dinic.init(m + n + 1, 0, m + n + 1);
		ll sum = 0;
		FOO(i,1,n) dinic.addEdge(m + i, m + n + 1, R());
		FOO(i,1,m){
			int ni = R(), pi = R();
			dinic.addEdge(0, i, pi); sum += pi;
			for(; ni; --ni)
				dinic.addEdge(i, m + R(), 1000000007);
		}
		W(sum - dinic.flow(), '\n');
		vector<int> tmp = dinic.scut();
		vector<int> ans;
		for(auto i: tmp)
			if(i >= m + 1 and i <= m + n) ans.pb(i - m);
		sort(AI(ans));
		W(ans.size(), '\n');
		for(auto i: ans) W(i, ' ');
		OB[OP++] = '\n';
	}
	write(1,OB,OP);
	return 0;
}
