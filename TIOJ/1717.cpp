#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

const int N = 1001;
int T, n, t[N], dp[N];
int head[N], to[N*N], prv[N*N], jizz;

inline int max(int a, int b){
	return a > b ? a : b;
}

int dfs(int u){
	int ans = 0;
	for(int v = head[u]; v != -1; v = prv[v])
		ans = max(ans, dp[to[v]] == 0 ? dfs(to[v]) : dp[to[v]]);
	return dp[u] = ans + t[u];
}

int main(){
	T = R();
	for(; T; --T){
		n = R(); jizz = 0;
		for(int i = 0; i <= n; ++i)
			head[i] = -1, dp[i] = 0;
		for(int i = 1; i <= n; ++i){
			to[jizz] = i, prv[jizz] = head[0], head[0] = jizz++;
			t[i] = R();
			for(int k = R(); k; --k)
				to[jizz] = R(), prv[jizz] = head[i], head[i] = jizz++;
		}
		printf("%d\n", dfs(0));
	}
}