#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];if(OP>65516)write(1,OB,OP),OP=0;}
inline void WP(int a, int b){
	OB[OP++] = '(';
	W(a);
	OB[OP++] = ',';
	W(b);
	OB[OP++] = ')';
	OB[OP++] = '\n';
}
const int N = 1500;
int n, m, a[N][N], x, y;
bool vis[N][N];

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
inline bool ok(int x, int y){ return x >= 0 and y >= 0 and x < n and y < m and !vis[x][y];}
void dfs(int x, int y){
	vis[x][y] = true;
	for(int d = 0; d < 4; ++d)
		if(ok(x + dx[d], y + dy[d]) and a[x + dx[d]][y + dy[d]] >= a[x][y])
			dfs(x + dx[d], y + dy[d]);
}

int main(){
	n = R(), m = R();
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			a[i][j] = R();
	x = R(), y = R();
	dfs(y, x);
	for(int j = 0; j < m; ++j)
		for(int i = 0; i < n; ++i)
			if(vis[i][j])
				WP(j, i);
	write(1,OB,OP);
	return 0;
}
