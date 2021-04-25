#pragma Ofast
#include<unistd.h>
inline char RC(){static char buf[1024],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,1024))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
const int N = 15;
inline void RM(int &a, bool &m){
	char c; a = 0;
	while((c = RC()) != 'm' and c != 'h' and c != -1);
	m = c == 'm';
	while((c = RC()) >= '0') a = a * 10 + c ^ '0';
}

int n, m;
bool dp[N*2+1][N*2+1];

int main(){
	for(int k = R(); k; --k){
		n = R(), m = R();
		for(int i = 1; i <= n * 2; ++i)
			for(int j = 1; j <= n * 2; ++j)
				dp[i][j] = false;

		int a1, a2;
		bool m1, m2;
		for(; m; --m){
			RM(a1, m1);
			RM(a2, m2);
			dp[a1 + !m1 * n][a2 + m2 * n] = true;
			dp[a2 + !m2 * n][a1 + m1 * n] = true;
		}

		for(int k = 1; k <= n * 2; ++k)
			for(int i = 1; i <= n * 2; ++i)
				for(int j = 1; j <= n * 2; ++j)
					dp[i][j] |= dp[i][k] and dp[k][j];

		bool ans = true;
		for(int i = 1; i <= n; ++i)
			ans &= !(dp[i][i + n] and dp[i + n][i]);
		
		puts(ans ? "GOOD" : "BAD");
	}
}