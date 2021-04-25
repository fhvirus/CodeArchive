#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#include<queue>
using namespace std;

int n, m, g[500][500], dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
bool vis[500][500];
struct point{
	int x, y, c;
	bool operator<(const point &rhs) const{
		return c > rhs.c;
	}
	bool in(){
		return x >= 0 and y >= 0 and x < n and y < m;
	}
};
priority_queue<point> pq;

int main(){
	while((n = R()) != 0){
		m = R(); pq = {};
		FOR(i, n) FOR(j, m){
			g[i][j] = R(), vis[i][j] = false;
			if(i == 0 or j == 0 or i == n-1 or j == m-1)
				pq.push({i, j, g[i][j]}), vis[i][j] = true;
		}
		long long ans = 0;
		while(!pq.empty()){
			point u = pq.top(); pq.pop();
			for(int d = 0; d < 4; ++d){
				point v = {u.x + dx[d], u.y + dy[d], 0};
				if(v.in() and !vis[v.x][v.y]){
					if(g[v.x][v.y] < u.c)
						ans += u.c - g[v.x][v.y],
						g[v.x][v.y] = u.c;
					v.c = g[v.x][v.y];
					pq.push(v), vis[v.x][v.y] = true;
				}
			}
		}
		printf("%lld\n", ans);
	}
}