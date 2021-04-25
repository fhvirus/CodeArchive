// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];if(OP>65516)write(1,OB,OP),OP=0;}
inline void WL(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];if(OP>65516)write(1,OB,OP),OP=0;}
inline void PC(char c){ OB[OP++]=c;}

#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
#define pb emplace_back
#define AI(x) begin(x),end(x)

const int N = 200002, L = 18;
int n, r;
int ri[N];
struct ADJ{
	int n, j;
	int to[N*2], pr[N*2], he[N];
	void init(int _n){
		n = _n, j = 0;
		for(int i = 0; i <= n; ++i) he[i] = -1;
	}
	void add(int u, int v){
		to[j] = v; pr[j] = he[u]; he[u] = j++;
		to[j] = u; pr[j] = he[v]; he[v] = j++;
	}
} adj, vir;
vector<int> nds[N];

int dep[N], vis[N], tot;
int st[L + 1][N * 2];
void dfs(int u, int p){
	vis[u] = tot++;
	st[0][vis[u]] = u;
	for(int e = adj.he[u], v; ~e; e = adj.pr[e]){
		if((v = adj.to[e]) == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
		st[0][tot++] = u;
	}
}
void process(){
	tot = 0;
	dfs(1, 0);
	int lb = __lg(tot) + 1;
	for(int l = 1; l < lb; ++l)
		for(int i = 0; i + (1<<l) < tot; ++i)
			st[l][i] = (
				dep[st[l-1][i]] < dep[st[l-1][i + (1<<(l-1))]]
				? st[l-1][i]
				: st[l-1][i + (1<<(l-1))]
			);
}
inline int lca(int u, int v){
	u = vis[u], v = vis[v];
	if(u > v) swap(u, v);
	int l = __lg(v - u);
	return (
		dep[st[l][u]] < dep[st[l][v - (1<<l) + 1]]
		? st[l][u]
		: st[l][v - (1<<l) + 1]
	);
}
int stk[N], top;
void buildVir(vector<int>& nds){
	sort(AI(nds), [](int u, int v){
		return vis[u] < vis[v];
	});
	
	vir.j = 0;
	stk[top = 1] = 1; vir.he[1] = -1;
	for(int i: nds){
		if(i == 1) continue;
		int l = lca(i, stk[top]);
		if(l != stk[top]){
			while(vis[l] < vis[stk[top - 1]])
				vir.add(stk[top], stk[top - 1]), --top;
			if(vis[l] > vis[stk[top - 1]]){
				vir.he[l] = -1;
				vir.add(l, stk[top]);
				stk[top] = l;
			} else vir.add(l, stk[top--]);
		}
		vir.he[i] = -1;;
		stk[++top] = i;
	}
	for(int i = 1; i < top; ++i)
		vir.add(stk[i], stk[i + 1]);
}

int curr;
ll dp;
int dps(int u, int p){
	int sz = (ri[u] == curr);
	for(int e = vir.he[u], v, cs; ~e; e = vir.pr[e]){
		if((v = vir.to[e]) == p) continue;
		cs = dps(v, u);
		if(cs != nds[curr].size())
			dp += 1ll * cs * cs * (dep[v] - dep[u]);
		sz += cs;
	}
	return sz;
}

void solve(){
	n = R(), r = R();
	adj.init(n);
	vir.init(n);
	for(int i = 0; i <= r; ++i) nds[i].clear();
	for(int i = 1; i <= n; ++i){
		ri[i] = R();
		nds[ri[i]].pb(i);
	}
	for(int i = 1, u, v, j = 0; i < n; ++i){
		u = R(), v = R();
		adj.add(u, v);
	}
	process();
	for(int i = 1; i <= r; ++i){
		buildVir(nds[i]);
		curr = i;
		dp = 0;
		dps(1, 0);
		W(i); PC(':'); PC(' ');
		WL(dp); PC('\n');
	}
	PC('\n');
}

int main(){
	for(int t = R(); t; --t) solve();
	write(1,OB,OP);
	return 0;
}
