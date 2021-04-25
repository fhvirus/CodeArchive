#include<cstdio>
#define FOR(i,n) for(int i = 0; i < n; ++i)

const int N = 21;
char g[N][N];
bool vis[N][N];
int xs[N*N], ys[N*N], c;
bool check(int i, int j, char e){
	if(i < 0 or j < 0 or i >= N or j >= N) return false;
	return g[i][j] == e;
}
void getv(int x, int y){
	static const int dx[4] = {1, -1, 0, 0};
	static const int dy[4] = {0, 0, 1, -1};
	int d = 2; // ->
	while(!vis[x][y]){
		vis[x][y] = true;
		xs[c] = x, ys[c] = y, ++c;
		do{
			x += dx[d];
			y += dy[d];
		} while(g[x][y] != '+');
		if(d <= 1){
			if(check(x + dx[2], y + dy[2], '-')){ d = 2; continue;}
			if(check(x + dx[3], y + dy[3], '-')){ d = 3; continue;}
		} else {
			if(check(x + dx[0], y + dy[0], '|')){ d = 0; continue;}
			if(check(x + dx[1], y + dy[1], '|')){ d = 1; continue;}			
		}
	}
	return;
}
int cross(int i, int j){
	return xs[i] * ys[j] - ys[i] * xs[j];
}
int geta(){
	int ans = cross(c - 1, 0);
	FOR(i,c - 1) ans += cross(i, i + 1);
	return ans > 0 ? ans / 2 : -ans / 2;
}
int main(){
	{ int i = 0; while(scanf("%s", g[i]) != -1) ++i;}
	int sx, sy;
	FOR(i,N) FOR(j,N) if(g[i][j] == '+'){
		sx = i, sy = j;
		break;
	}
	getv(sx, sy);
	printf("%d", geta());
}