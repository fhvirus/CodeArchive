#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
inline char readchar(){
	const int S = 1<<10;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}

char s[1000], t[1000];
short dp[2][1001], m, n, roll;

inline short min(int a, int b, int c){
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int main(){
	char c;
	while((c=readchar()) != '\n') s[m++] = c;
	s[m] = '\0';
	while((c=readchar()) != '\n' and c != EOF) t[n++] = c;
	t[n] = '\0';
	for(int i = 0; i <= n; ++i) dp[0][i] = i;
	dp[1][0] = 1;
	roll = 1;

	for(int i = 1; i <= m; ++i){
		dp[roll][0] = i;
		for(int j = 1; j <= n; ++j){
			if(s[i-1] == t[j-1])
				dp[roll][j] = dp[1-roll][j-1];
			else
				dp[roll][j] = min(
					dp[1-roll][j],
					dp[roll][j-1],
					dp[1-roll][j-1]
				) + 1;
		}
		roll = 1 - roll;
	}

	printf("%d", dp[1-roll][n]);
}