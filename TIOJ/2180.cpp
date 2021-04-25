//Knapsack DP is harder than FFT.
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<queue>
#include<tuple>
using namespace std;

#define FOR(i,n) for(int i=0;i<(n);++i)
template<typename I> bool chmin(I &a, I b){ return b < a ? (a = b, true) : false;} 

const int N = 1005, INF = 1e9;
typedef tuple<int, int, int> tti;
int r, c, rs, cs, rd, cd;
int n;
int g[N][N], d[N][N];
bool vis[N][N];
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

int main(){
	r = R(), c = R(), rs = R(), cs = R(), rd = R(), cd = R();
	n = R();
	FOR(i, r) FOR(j, c)	g[i][j] = -1;
	FOR(i, r) FOR(j, c) d[i][j] = INF;
	FOR(i, n){
		g[R()][R()] = R();
	}
	d[rs][cs] = 0;
	g[rs][cs] = 0;
	g[rd][cd] = 0;
	priority_queue<tti, vector<tti>, greater<tti>> pq;
	pq.emplace(0, rs, cs);
	while(!pq.empty()){
		auto[dd, x, y] = pq.top(); pq.pop();
		if(vis[x][y]) continue;
		if(x == rd and y == cd) break;
		vis[x][y] = true;
		FOR(i,4){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(nx < 0 or nx >= r or ny < 0 or ny >= c or g[nx][ny] == -1 or vis[nx][ny]) continue;
			if(chmin(d[nx][ny], max(dd, g[nx][ny]))) pq.emplace(d[nx][ny], nx, ny);
		}
	}
	W(d[rd][cd]);
	return 0;
}
