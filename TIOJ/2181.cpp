#include<unistd.h>
char OB[20]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';}

const int N = 1005;
int a, n, dp[N];
int main(){
	a = R(), n = R();
	for(int x, y; n; --n){
		x = R(), y = R();
		for(int j = a; j >= y; --j)
            if(dp[j] < dp[j - y] + x) dp[j] = dp[j - y] + x;
	}
	int m = 0, s = 0;
	for(int i = 0; i <= a; ++i) if(m < dp[i]) m = dp[i], s = i;
	W(m); W(s); write(1,OB,OP);
	return 0;
}
