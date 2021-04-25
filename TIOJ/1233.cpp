#pragma Ofast
#pragma loop-opt(on)
#pragma GCC target("avx,avx2")
#include<cstdio>

const int N = 512;
const int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int jiz[11] = {0, 1, 2, 4, 6, 10, 12, 14, 16, 18, 20};
int m, n, ans;
char g[N][N];

void dfs(int i, int j){
	g[i][j] = '0';
	for(int d = 0; d < 8; ++d)
		if(i + dx[d] >= 0 and i + dx[d] < m and j + dy[d] >= 0 and j + dy[d] < n and g[i + dx[d]][j + dy[d]] == '1')
			dfs(i + dx[d], j + dy[d]);
}

int main(){
	scanf("%d%d", &m, &n);
	for(int i = 0; i < m; ++i)
		scanf("%s", g[i]);
	for(int i = 0; i < m; ++i)
		for(int j = 0; j < n; ++j)
			if(g[i][j] == '1')
				++ans, dfs(i, j);
	if(ans >= 20){ puts("10"); return 0;}
	for(int i = 0; i <= 10; ++i)
		if(jiz[i] >= ans){ printf("%d", i); return 0;}
}