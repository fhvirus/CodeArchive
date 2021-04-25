#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void RS(char s[]){ static int p; while((s[0] = RC()) < '0'); p = 1; while((s[p++] = RC()) >= '0'); s[p-1] = '\0';}
#include<cstdio>
const int N = 1000, M = 32768;
int n, v, e;
bool vis[N];
int top[N], jiz;
int adj[N][N];
int sum[N], cnt[N];
char name[N][22];

void dfs(int u){
	vis[u] = true;
	for(int i = 1; i < v; ++i)
		if(adj[u][i] != -1 and !vis[i])
			dfs(i);
	top[--jiz] = u;
}

inline void solve(){
	n = R(), v = R(), e = R();
	for(int i = 0; i < v; ++i){
		sum[i] = cnt[i] = 0;
		vis[i] = false;
		for(int j = 0; j < v; ++j)
			adj[i][j] = -1;
	}
	for(int i = 1; i <= n; ++i)
		RS(name[i]);
	for(int i = 0, a, b, c; i < e; ++i){
		a = R(), b = R(), c = R();
		adj[a][b] = c % M;
	}

	jiz = v;
	dfs(0);

	sum[0] = 0, cnt[0] = 1;
	for(int i = 0; i < v; ++i){
		int u = top[i];
		for(int j = 0; j < v; ++j){
			if(adj[u][j] != -1){
				sum[j] = (sum[j] + sum[u] + adj[u][j] * cnt[u] % M) % M;
				cnt[j] = (cnt[j] + cnt[u]) % M;
			}
		}
	}

	for(int i = 1; i <= n; ++i)
		printf("%s: %d\n", name[i], sum[i]);
}

int main(){
	int t = R();
	for(int i = 1; i <= t; ++i){
		printf("Game #%d\n", i);
		solve();
	}
	return 0;
}