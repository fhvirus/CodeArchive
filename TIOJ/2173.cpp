#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#pragma GCC loop-opt(on)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

inline int max(int a, int b){ return a > b ? a : b;}

const int N = 105;

int m, n, g[N][N], dp[2][N][N], roll;
bool vis[N][N];

inline bool good(int i, int j){
	return j >= 0 and i - j >= 0 and j <= m and i - j <= n and g[j][i - j] != -1 and vis[j][i-j];
}

int main(){
	m = R(), n = R(); vis[0][0] = true;
	for(int i = 0; i < m; ++i)
		for(int j = 0; j < n; ++j){
			g[i][j] = R();
			if(g[i][j] == -1) vis[i][j] = false;
			else{
				if(i > 0) vis[i][j] |= vis[i-1][j];
				if(j > 0) vis[i][j] |= vis[i][j-1];
			}
		}

	if(!vis[m-1][n-1]){ W(0); return 0;}

	// from (0, 0) to (m-1, n-1)
	for(int i = 0; i <= m + n - 2; ++i, roll = 1 - roll){
		for(int j = 0; j <= i; ++j){
			if(!good(i, j)) continue;
			for(int k = 0; k <= i; ++k){
				if(!good(i, k)) continue;
				dp[roll][j][k] = g[j][i - j] + (j != k ? g[k][i - k] : 0);

				int mx = 0;
				if(good(i-1, j) and good(i-1, k))
					mx = max(mx, dp[1 - roll][j][k]);
				if(good(i-1, j) and good(i-1, k-1))
					mx = max(mx, dp[1 - roll][j][k-1]);
				if(good(i-1, j-1) and good(i-1, k))
					mx = max(mx, dp[1 - roll][j-1][k]);
				if(good(i-1, j-1) and good(i-1, k-1))
					mx = max(mx, dp[1 - roll][j-1][k-1]);
				dp[roll][j][k] += mx;
			}
		}
	}
	W(dp[1 - roll][m-1][m-1]);
	return 0;
}