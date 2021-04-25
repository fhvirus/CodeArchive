#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S];
int outp;
inline void W(int n){
	if(n >= 10) outbuf[outp++] = n / 10 + '0';
	outbuf[outp++] = n % 10 + '0';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}
inline void W(int z, int y, int x){
	outbuf[outp++] = '(';
	W(x);
	outbuf[outp++] = ',';
	W(y);
	outbuf[outp++] = ',';
	W(z);
	outbuf[outp++] = ')';
}
#include<queue>
#include<stack>
using namespace std;

bool G[50][50][50];
int dist[50][50][50];
int pre[50][50][50];
int x, y, z;

struct point{ int x, y, z;};

const int dx[6] = {1, -1, 0, 0, 0, 0};
const int dy[6] = {0, 0, 1, -1, 0, 0};
const int dz[6] = {0, 0, 0, 0, 1, -1};

int main(){
	z = R(); y = R(); x = R();
	FOR(i,x) FOR(j,y) FOR(k,z) G[i][j][k] = (R()==1);

	queue<point> Q;
	dist[0][0][0] = 1;
	Q.push({0, 0, 0});
	while(!Q.empty()){
		point now = Q.front(); Q.pop();
		for(int i = 0; i < 6; i++){
			point nxt = {now.x+dx[i], now.y+dy[i], now.z+dz[i]};
			if(nxt.x >= x or nxt.x < 0) continue;
			if(nxt.y >= y or nxt.y < 0) continue;
			if(nxt.z >= z or nxt.z < 0) continue;
			if(dist[nxt.x][nxt.y][nxt.z]) continue;
			if(!G[nxt.x][nxt.y][nxt.z]){
				dist[nxt.x][nxt.y][nxt.z] = dist[now.x][now.y][now.z] + 1;
				pre[nxt.x][nxt.y][nxt.z] = i;
				Q.push(nxt);
			}
		}
	}

	if(!dist[x-1][y-1][z-1] or G[0][0][0]){
		puts("no route");
		return 0;
	}

	stack<point> ans;
	int i;
	x--, y--, z--;
	while(x or y or z){
		ans.push({x, y, z});
		i = pre[x][y][z];
		x -= dx[i], y -= dy[i], z -= dz[i];
	}

	W(1, 1, 1);
	while(!ans.empty()){
		point now = ans.top();
		outbuf[outp++] = '-'; outbuf[outp++] = '>';
		W(now.x+1, now.y+1, now.z+1);
		ans.pop(); 
	}
	fwrite(outbuf, 1, outp, stdout);
	return 0;
}