#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

inline int max(int a, int b){ return a > b ? a : b;}

const int N = 3000;
int n, m, g[N][N];
bool vis[N][N];

int x[N*N], y[N*N], ptr;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
inline bool in(int i, int j){ return i >= 0 and j >= 0 and i < n and j < m and !vis[i][j];}
int dfs(int i, int j, int id){
	int ans = 0;
	vis[0][0] = true;
	ptr = 0;
	x[ptr] = i, y[ptr] = j, ++ptr;
	while(ptr > 0){
		int i = x[ptr-1], j = y[ptr-1]; --ptr;
		for(int d = 0; d < 4; ++d)
			if(in(i + dx[d], j + dy[d]) and g[i + dx[d]][j + dy[d]] == id)
				++ans,
				x[ptr] = i + dx[d], y[ptr] = j + dy[d], ++ptr,
				vis[i + dx[d]][j + dy[d]] = true;
	}
	return ans;
}

int main(){
	n = R(), m = R();
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			g[i][j] = R();

	int ans = 0;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			if(!vis[i][j])
				ans = max(ans, dfs(i, j, g[i][j]));

	W(ans);
	return 0;
}