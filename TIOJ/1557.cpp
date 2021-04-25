// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int N = 10001, M = 100001, MOD = 1<<30;
int n, m;
int he[N], to[M], pr[M];
bool vis[N];
int stk[N], top;
int dp[N];

void dfs(int u){
	vis[u] = true;
	for(int v = he[u]; v != -1; v = pr[v])
		if(!vis[to[v]]) dfs(to[v]);
	stk[top++] = u;
}

int main(){
	n = R(), m = R();
	for(int i = 1; i <= n; ++i) he[i] = -1;
	for(int u, v, i = 0; i < m; ++i){
		u = R(), v = R();
		to[i] = v; pr[i] = he[u]; he[u] = i;
	}

	for(int i = 1; i <= n; ++i) if(!vis[i]) dfs(i);

	int V = R(), D = R(); dp[V] = 1;
	for(int i = 1; i <= n; ++i){
		int u = stk[--top];
		for(int v = he[u]; v != -1; v = pr[v]){
			dp[to[v]] += dp[u];
			if(dp[to[v]] >= MOD) dp[to[v]] -= MOD;
		}
	}
	W(dp[D]);
	return 0;
}
