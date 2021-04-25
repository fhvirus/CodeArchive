#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
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

char m[100][100], cur;
int w, h, E=0, G=0;

const int dx[8] = {-1, -1, -1,  0,  0,  1,  1,  1};
const int dy[8] = {-1,  0,  1, -1,  1, -1,  0,  1};

inline void dfs(int x, int y){
	m[x][y] = 'V';
	for(int i = 0; i < 8; i++){
		if(x+dx[i] >= h or x+dx[i] < 0) continue;
		if(y+dy[i] >= w or y+dy[i] < 0) continue;
		if(m[x+dx[i]][y+dy[i]] == cur)
			dfs(x+dx[i], y+dy[i]);
	}
}

int main(){
	w = R(); h = R();
	FOR(i,h) FOR(j,w){
		while((m[i][j] = readchar())==' ' or m[i][j] == '\n');
	}
	FOR(i,h) FOR(j,w)
		if(m[i][j] == '-') cur = '-', dfs(i, j), E++;
		else if(m[i][j] == 'G') cur = 'G', dfs(i, j), G++;
	printf("%d %d", G, E);
	return 0;
}