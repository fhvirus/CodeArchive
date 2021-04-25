#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")
#pragma loop_opt(on)
#include<cstdio>
inline char readchar(){
	const int S = 1<<16;
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c=readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
const int N = 1e6;
int n, ans = 8e7;
int head[N], to[N<<1], prv[N<<1];

inline int min(int a, int b){ return a < b ? a : b;}
inline int max(int a, int b){ return a > b ? a : b;}

int dfs(int u, int p){
	int sz = 1, mx = 0;
	for(int v = head[u]; v != -1; v = prv[v])
		if(to[v] != p){
			int s = dfs(to[v], u);
			sz += s;
			mx = max(mx, s);
		}
	if(u != 0) mx = max(mx, n - sz);
	ans = min(ans, mx);
	return sz;
}

int main(){
	n = R();
	for(int i = 0; i < n; ++i) head[i] = -1;
	for(int i = 1, u, v, j = 0; i < n; ++i){
		u = R(), v = R();
		to[j] = v; prv[j] = head[u]; head[u] = j++;
		to[j] = u; prv[j] = head[v]; head[v] = j++;
	}
	dfs(0, 0);
	printf("%d", ans);
	return 0;
}