#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[256],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,256))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
using namespace std;

const int N = 125, M = 225;
int m, n, a, b, c, d, dp[2][M][M];
int main(){
	m = R(), n = R();
	a = R(), b = R(), c = R(), d = R();
	for(int k = 1; k <= n; ++k)
		for(int i = k; i <= m; ++i)
			for(int j = k; j <= m; ++j)
				dp[k&1][i][j] = max({
					dp[(k-1)&1][i-1][j-1] + (a * (k - 1) + b * (i - 1) + c * (j - 1)) % d,
					dp[k&1][i-1][j],
					dp[k&1][i][j-1]
				});

	W(dp[n&1][m][m]);
	return 0;
}