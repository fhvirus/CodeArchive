#pragma O1
#include<cstdio>
inline char readchar(){
	const int S = 1<<12;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline short min(short a, short b){
	return a < b ? a : b;
}

const int N = 32768;
int n, m;
bool vis[N];
short to[N], head[N], prv[N], dp[2][N];

void dfs(short u){
	if(vis[u]) return;
	vis[u] = true;
	dp[0][u] = 0;
	dp[1][u] = 1;
	for(short v = head[u]; v != -1; v = prv[v]){
		dfs(to[v]);
		dp[0][u] += dp[1][to[v]];
		dp[1][u] += min(dp[0][to[v]], dp[1][to[v]]);
	}
}
int main(){
	n = R();
	for(int i = 0; i < n; ++i) head[i] = -1;
	for(int i = 0, j, k = 0; i < n; ++i)
		for(m = R(); m; --m){
			j = R();
			to[k] = j;
			prv[k] = head[i];
			head[i] = k++;
		}
	dfs(0);
	printf("%d", min(dp[0][0], dp[1][0]));
}