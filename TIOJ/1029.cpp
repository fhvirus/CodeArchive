#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<unistd.h>
char OB[30]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';}


inline int max(int a, int b){ return a > b ? a : b;}
inline int min(int a, int b){ return a < b ? a : b;}

const int N = 1001;
int n, a[N], dp[2][N]; // len, l

int main(){
	n = R();
	for(int i = 1; i <= n; ++i) dp[0][i] = a[i] = R();
	for(int i = 1; i <= n; ++i) a[i] += a[i-1];
	int roll = 1;
	for(int len = 2; len <= n; ++len){
		for(int l = 1; l + len - 1 <= n; ++l){
			dp[roll][l] = 
				a[l + len - 1] - a[l - 1] - min(
					dp[1 - roll][l],
					dp[1 - roll][l + 1]
				);
		}
		roll = 1 - roll;
	}

	W(dp[1 - roll][1]), W(a[n] - dp[1 - roll][1]);
	write(1,OB,OP);
}