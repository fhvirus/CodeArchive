// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
#include<bitset>
using namespace std;
const int N = 3003;
int n, x2, y2, z2;
bitset<N> vis[N];

void dfs(int x, int y, int z){
	if(vis[x2][y2]) return;
	vis[x][y] = true;
	if(!vis[y][x]) dfs(y, x, z);
	if(!vis[x][z]) dfs(x, z, y);
	if(!vis[z][y]) dfs(z, y, x);
	int nx = 2 * y - x + 1, ny = 2 * x - y - 1;
	if(nx >= 0 and ny >= 0 and nx <= n and ny <= n and !vis[nx][ny])
		dfs(nx, ny, z);
}

int main(){
	int x1, y1, z1;
	while(n = R()){
		x1 = R(), y1 = R(), z1 = R(), x2 = R(), y2 = R(), z2 = R();
		if(x1 + y1 + z1 != x2 + y2 + z2){
			puts("No");
			continue;
		}
		for(int i = 0; i <= n; ++i) vis[i].reset();
		dfs(x1, y1, z1);
		puts(vis[x2][y2] ? "Yes" : "No");
	}
	return 0;
}