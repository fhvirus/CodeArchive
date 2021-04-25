// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[40]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline char EEK(){static char c; while((c=RC())<'0');return c;}
inline void W(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';}

#include<algorithm>
using namespace std;

const int N = 5005;
int n, m;
int dp[2][N];
char g;
long long sum; int ans;

int32_t main(){
	n = R(), m = R();

	int r = 0;

	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m; ++j){
			g = EEK();
			if(g == '0'){
				dp[r][j] = min({dp[1-r][j-1], dp[1-r][j], dp[r][j-1]}) + 1;
				sum += dp[r][j];
				ans = max(ans, dp[r][j]);
			} else dp[r][j] = 0;
		}
		r = 1 - r;
	}

	W(sum), W(ans), write(1,OB,OP);
	return 0;
}
