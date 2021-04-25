#pragma Ofast
#pragma loop-opt(on)
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline int min(int a, int b){ return a < b ? a : b;}
#include<cstdio>

const int N = 1e5 + 225;
int T, n, m;
bool ans;

int head[N], to[N], prv[N];

bool leave[N];
int pre[N], cnt, low[N];
bool dfs(int u, int p){
	low[u] = pre[u] = ++cnt;

	int eek = 0;
	for(int v = head[u]; v != -1; v = prv[v]){
		if(leave[to[v]]) return false;
		if(pre[to[v]]) ++eek, low[u] = min(low[u], pre[to[v]]);
		else{
			if(!dfs(to[v], u)) return false;
			low[u] = min(low[u], low[to[v]]);
			if(low[to[v]] > pre[u]) return false;
			if(low[to[v]] < pre[u]) ++eek;
		}
	}

	leave[u] = true;
	return eek < 2;
}

int main(){
	T = R();
	while(T--){
		n = R(), m = R(), cnt = 0;

		for(int i = 0; i < n; ++i)
			head[i] = -1, leave[i] = false, pre[i] = 0;

		for(int i = 0, a; i < m; ++i)
			a = R(), to[i] = R(), prv[i] = head[a], head[a] = i;

		ans = dfs(0, 0);
		for(int i = 0; i < n and ans; ++i)
			if(!pre[i]) ans = false;

		puts(ans ? "YES" : "NO");
	}
	return 0;
}