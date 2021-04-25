#pragma Ofast
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65524)write(1,OB,OP),OP=0;}
#include<algorithm>
using namespace std;

const int N = 111;
const int INF = 1e9 + 7;
int n, a[N][N], dp[N][N];

int main(){
	while((n = R()) != 0){
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= i; ++j)
				a[i][j] = R();
		for(int i = 1; i <= n; ++i)
			dp[i][i+1] = dp[i][0] = INF;

		dp[1][1] = a[1][1];
		int ans = dp[1][1];
		for(int i = 2; i <= n; ++i){
			for(int j = 1; j <= i; ++j){
				dp[i][j] = min(
					max(dp[i-1][j], a[i][j]) + 1,
					max(dp[i-1][j-1], a[i][j]) + 1
				);
				ans = max(ans, dp[i][j]);
			}
		}
		W(ans);
	}
	write(1,OB,OP);
	return 0;
}