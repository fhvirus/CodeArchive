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
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

int n, m, k, x1, y1, x2, y2, dx, dy, roll = 1, cnt;
bool dp[2][100][100];

int main(){
	n = R(); m = R(); x1 = R(); y1 = R(); x2 = R(); y2 = R(); k = R();
	dp[0][x1][y1] = true;

	FOR(i,k){
		dx = R();
		dy = dx % m;
		dx %= n;
		cnt = 0;
		FOR(x,n)FOR(y,m){
			cnt += (dp[roll][x][y] = 
				dp[1-roll][x + dx < n ? x + dx : x + dx - n][y] |
				dp[1-roll][x - dx < 0 ? x - dx + n : x - dx][y] |
				dp[1-roll][x][y + dy < m ? y + dy : y + dy - m] |
				dp[1-roll][x][y - dy < 0 ? y - dy + m : y - dy]
			);
		}
		if(cnt == n * m){
			puts("YES");
			return 0;
		}
		roll = 1-roll;
	}
	puts(dp[1-roll][x2][y2] ? "YES" : "NO");
	return 0;
}