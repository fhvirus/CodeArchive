#include<cstdio>
inline char R(){
	char ans = 0, c = getchar_unlocked();
	while((c<'0'||c>'9')&&c!=EOF) c=getchar_unlocked();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=getchar_unlocked();
	return ans;
}
char grid[10][18] = {
	"*****************",
	"*...*.......**..*",
	"**..*....*.*.*..*",
	"*......*.**.**.**",
	"*..**...**..**.**",
	"**.....**..*.*..*",
	"*....*..........*",
	"*.....****.*...**",
	"****.*.*........*",
	"*****************"
}, dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
const int INF = 8e7;
int getOnFire[10][17], dist[10][17];
int fx, fy, t, sx, sy, ex, ey;
inline int abs(int a){
	return a < 0 ? -a : a;
}
inline bool ok(int x, int y){
	return x < 10 and x >= 0 and y < 17 and y >= 0 and grid[x][y] == '.';
}

int qx[170], qy[170], qz[170];
int qh, qt;
int main(){
	fx = R(), fy = R();
	t = R();
	sx = R(), sy = R(), ex = R(), ey = R();

	getOnFire[fx][fy] = 1;
	grid[ex][ey] = '*';
	qx[qt] = fx, qy[qt] = fy, qz[qt] = 1, ++qt;
	while(qt > qh){
		int x = qx[qh], y = qy[qh], z = qz[qh]; ++qh;
		for(int d = 0; d < 4; ++d)
			if(ok(x + dx[d], y + dy[d]) and getOnFire[x + dx[d]][y + dy[d]] == 0)
				getOnFire[x + dx[d]][y + dy[d]] = z + 1,
				qx[qt] = x + dx[d], qy[qt] = y + dy[d], qz[qt] = z + 1, ++qt;
	}
	grid[ex][ey] = '.';
	getOnFire[ex][ey] = INF;

	dist[sx][sy] = t;
	qt = qh = 0;
	qx[qt] = sx, qy[qt] = sy, qz[qt] = t, ++qt;
	while(qt > qh){
		int x = qx[qh], y = qy[qh], z = qz[qh]; ++qh;
		if(z >= getOnFire[x][y]) continue;
		if(x == ex and y == ey) break;
		for(int d = 0; d < 4; ++d)
			if(ok(x + dx[d], y + dy[d]) and dist[x + dx[d]][y + dy[d]] == 0)
				dist[x + dx[d]][y + dy[d]] = z + 1,
				qx[qt] = x + dx[d], qy[qt] = y + dy[d], qz[qt] = z + 1, ++qt;
	}

	if(dist[ex][ey] == 0) puts("Help!");
	else printf("%d", dist[ex][ey] - t);
}