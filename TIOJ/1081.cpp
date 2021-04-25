#include<cstdio>
inline char readchar(){
	const int S = 1<<14;
	static char buf[S], *p = buf, *q = buf;
	if(p==q and (q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int readint(){
	int ans = 0, c = readchar();
	while((c<'0' or c>'9')and c!=EOF) c=readchar();
	while(c>='0' and c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

int n, m, c, ans, thresh,
	dx[8] = {1, 0, -1, 1, -1, 1, 0, -1},
	dy[8] = {1, 1, 1, 0, 0, -1, -1, -1};
bool g[1002][1002];
inline bool in(int i, int j){
	return i >= 0 and j >= 0 and i < n and j < m;
}
void dfs(int i, int j){
	g[i][j] = 0;
	for(int k = 0; k < 8; ++k)
		if(g[i+dx[k]][j+dy[k]])
			dfs(i+dx[k], j+dy[k]);
}

int main(){
	while(true){
		n = readint(), m = readint();
		if(n==0) break;
		thresh = n*m>>2, ans = 0;
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= m; ++j){
				do{
					c = readchar();
				}while(c < '0');
				g[i][j] = (c=='1');
			}
		}
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= m; ++j){
				if(g[i][j]) ++ans, dfs(i, j);
				if(ans > thresh) break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}