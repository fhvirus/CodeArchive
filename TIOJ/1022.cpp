#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

const int N = 600, INF = 8e7;
int k, m, n;
int h[N][N], dist[N][N], X[N*N], Y[N*N], head, tail, x, y;
const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};

inline int abs(int a){
	return a < 0 ? -a : a;
}
inline bool ok(int x, int y, int d){
	return x + dx[d] < m && x + dx[d] >= 0 && y + dy[d] < n and y + dy[d] >= 0 and abs(h[x][y] - h[x + dx[d]][y + dy[d]]) <= 5;
}

int main(){
	k = R();
	for(; k; --k){
		m = R(), n = R();
		FOR(i,m)FOR(j,n) h[i][j] = R(), dist[i][j] = INF;
		dist[0][0] = 0;
		head = tail = 0;
		X[tail] = 0, Y[tail] = 0, ++tail;
		while(tail > head){
			x = X[head], y = Y[head], ++head;
			if(x == m-1 and y == n-1) break;
			for(int d = 0; d < 4; ++d){
				if(ok(x, y, d) && dist[x + dx[d]][y + dy[d]] == INF)
					dist[x + dx[d]][y + dy[d]] = dist[x][y] + 1,
					X[tail] = x + dx[d], Y[tail] = y + dy[d], ++tail;
			}
		}
		printf("%d\n", dist[m-1][n-1]);
	}
}