// Knapsack DP is harder than FFT.
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<vector>
#include<cstring>
#include<queue>
using namespace std;

#define pb emplace_back
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)

struct Dinic{
	static const int N = 2e5 + 225;
	static const int INF = 1000000007;
	struct Edge{
		int to, cap, rev;
		Edge(){}
		Edge(int t, int c, int r):
			to(t), cap(c), rev(r){}
	};
	vector<Edge> G[N];
	void addEdge(int from, int to, int cap){
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
	int flow(){
		int ret = 0;
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
} dinic;

// const int N = 2e5 + 225, E = 230032;

// int head[N], to[E*2], prv[E*2], e;
// int match[N], vis[N], eek;

// bool dfs(int u){
// 	if(vis[u] == eek) return false;
// 	vis[u] = eek;
// 	for(int v = head[u]; v != -1; v = prv[v])
// 		if(!match[to[v]] or dfs(match[to[v]])){
// 			match[u] = to[v];
// 			match[to[v]] = u;
// 			return true;
// 		}
// 	return false;
// }

// int gm(int p){
// 	int ans = 0;
// 	FOO(i,1,p) if(!match[i])
// 		for(int j = head[i]; j != -1; j = prv[j])
// 			if(!match[to[j]]){
// 				match[i] = to[j];
// 				match[to[j]] = i;
// 				++ans;
// 				break;
// 			}
// 	return ans;
// }

void solve(){
	// int p, q, k; p = R(), q = R(), k = R(); e = 0;
	// FOO(i,1,p + q) head[i] = -1;
	// FOO(i,1,p + q) match[i] = 0;
	// int ans = 0;
	// for(int u, v; k; --k){
	// 	u = R(), v = R() + p;
	// 	to[e] = v; prv[e] = head[u]; head[u] = e++;
	// }
	// ++eek;
	// ans += gm(p);
	// FOO(i,1,p) if(!match[i]) ++eek, ans += dfs(i);
	// W(ans);
	int p, q, k; p = R(), q = R(), k = R();
	dinic.init(p + q + 1, 0, p + q + 1);
	FOO(i,1,p) dinic.addEdge(0, i, 1);
	FOO(i,1,q) dinic.addEdge(p + i, p + q + 1, 1);
	for(int u, v; k; --k){
		u = R(), v = R() + p;
		dinic.addEdge(u, v, 1);
	}
	W(dinic.flow());
}

int main(){
	for(int t = R(); t; --t) solve();
	write(1,OB,OP);
	return 0;
}
