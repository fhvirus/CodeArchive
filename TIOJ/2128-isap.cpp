// Knapsack DP is harder than FFT.
// #pragma GCC optimize("Ofast")
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

struct ISAP{
	static const int N = 4004;
	static const int INF = 0x3f3f3f3f;
	struct Edge{
		int to, cap, rev;
		Edge(){}
		Edge(int t, int c, int r): to(t), cap(c), rev(r){}
	};
	vector<Edge> G[N];
	void addEdge(int from, int to, int cap){
		G[from].pb(to, cap, (int)G[to].size());
		G[to].pb(from, 0, (int)G[to].size()-1);
	}
	int n, s, t;
	int dis[N], iter[N], gap[N];
	bool vis[N];
	void init(int _n, int _s, int _t){
		n = _n, s = _s, t = _t;
		for(int i = 0; i <= n; ++i){
			G[i].clear();
			dis[i] = INF;
			iter[i] = 0;
			gap[i] = 0;
			vis[i] = false;
		}
	}
	void bfs(){
		memset(dis, INF, sizeof(dis));
		dis[t] = 0;
		queue<int> q; q.push(t);
		while(!q.empty()){
			int u = q.front(); q.pop();
			for(auto e: G[u]){
				if(e.cap == 0 and dis[e.to] == INF){
					dis[e.to] = dis[u] + 1;
					q.push(e.to);
				}
			}
		}
		if(dis[s] == INF) return;
		memset(vis, 0, sizeof(vis));
		vis[s] = true;
		q.push(s);
		while(!q.empty()){
			int u = q.front(); q.pop();
			if(dis[u] != INF) gap[dis[u]]++;
			for(auto e: G[u]){
				if(e.cap > 0 and !vis[e.to]){
					vis[e.to] = true;
					q.push(e.to);
				}
			}
		}
	}
	bool ok;
	int dfs(int now, int flow){
		if(now == t) return flow;
		for(int &i = iter[now]; i < (int) G[now].size(); ++i){
			auto &e = G[now][i];
			if(e.cap > 0 and dis[e.to] + 1 == dis[now]){
				int ret = dfs(e.to, min(e.cap, flow));
				if(ret > 0){
					e.cap -= ret;
					G[e.to][e.rev].cap += ret;
					return ret;
				}
			}
		}
		if(!ok) return 0;
		--gap[dis[now]];
		if(gap[dis[now]] == 0){
			ok = false;
			return 0;
		}
		dis[now] = INF;
		for(int i = 0; i < (int)G[now].size(); ++i){
			if(G[now][i].cap > 0) dis[now] = min(dis[now], dis[G[now][i].to] + 1);
		}
		if(dis[now] != INF) gap[dis[now]]++;
		iter[now] = 0;
		return 0;
	}
	ll flow(){
		ll ret = 0;
		bfs();
		ok = true;
		while(dis[s] < n and ok) ret += dfs(s, INF);
		return ret;
	}
	vector<int> scut(){
		vector<bool> vv(N, false);
		queue<int> q;
		q.push(0);
		vector<int> ans;
		while(!q.empty()){
			int u = q.front(); q.pop();
			if(vv[u]) continue;
			vv[u] = true;
			ans.pb(u);
			for(Edge e: G[u]){
				if(e.cap > 0 and !vv[e.to])
					q.push(e.to);
			}
		}
		return ans;
	}
} isap;



char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+fread(buf,1,65536,stdin))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(ll n, char e){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)fwrite(OB,1,OP,stdout),OP=0;}
int32_t main(){
	int t, n, m;
	for(t = R(); t; --t){
		n = R(), m = R();
		isap.init(m + n + 2, 0, m + n + 1);
		ll sum = 0;
		FOO(i,1,n) isap.addEdge(m + i, m + n + 1, R());
		FOO(i,1,m){
			int ni = R(), pi = R();
			isap.addEdge(0, i, pi); sum += pi;
			for(; ni; --ni)
				isap.addEdge(i, m + R(), 1000000007);
		}
		W(sum - isap.flow(), '\n');
		vector<int> tmp = isap.scut();
		vector<int> ans;
		for(auto i: tmp)
			if(i >= m + 1 and i <= m + n) ans.pb(i - m);
		sort(AI(ans));
		W(ans.size(), '\n');
		for(auto i: ans) W(i, ' ');
		OB[OP++] = '\n';
	}
	fwrite(OB,1,OP,stdout);
	return 0;
}

