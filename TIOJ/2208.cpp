#include<iostream>
#include<cassert>
#include<bitset>
#include<queue>
#include<tuple>
using namespace std;

const int kN = 1000;
const int INF = 1e9;

int N, M;
int P, Q;
int X, Y;
bitset<kN> a[kN], vis[kN];

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
inline bool ok(int x, int y){
	return 0 <= x and x < N and 0 <= y and y < M and !a[x][y];
}
int bfs(int sx, int sy, int tx, int ty){
	if(sx == tx and sy == ty) return 0;
	for(int i = 0; i < N; ++i)
		for(int j = 0; j < M; ++j)
			vis[i][j] = 0;

	queue<tuple<int, int, int>> q;
	vis[sx][sy] = 1; q.emplace(sx, sy, 0);
	while(!q.empty()){
		auto [x, y, d] = q.front(); q.pop();
		for(int dir = 0; dir < 4; ++dir)
			for(int step: {P, Q}){
				int nx = x + dx[dir] * step;
				int ny = y + dy[dir] * step;
				if(ok(nx, ny) and !vis[nx][ny]){
					if(nx == tx and ny == ty)
						return d+1;
					vis[nx][ny] = true;
					q.emplace(nx, ny, d+1);
				}
			}
	}
	return INF;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	assert(cin >> N >> M);
	assert(1 <= N and N <= kN);
	assert(1 <= M and M <= kN);

	assert(cin >> P >> Q);
	assert(0 <= P and P < min(N, M));
	assert(0 <= Q and Q < min(N, M));

	assert(cin >> X >> Y);
	assert(1 <= X and X <= N);
	assert(1 <= Y and Y <= M);
	--X, --Y;

	for(int i = 0; i < N; ++i)
		for(int j = 0; j < M; ++j){
			int v; assert(cin >> v);
			assert(v == 0 or v == 1);
			a[i][j] = v;
		}

	assert(!a[0][0]);
	assert(!a[X][Y]);
	assert(!a[N-1][M-1]);

	int ans = bfs(0, 0, X, Y) + bfs(X, Y, N-1, M-1);
	cout << (ans >= INF ? -1 : ans) << '\n';
	return 0;
}


