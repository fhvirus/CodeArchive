#include<unistd.h>
char OB[4096]; int OP;
inline char RC(){static char buf[4096],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,4096))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>4076)write(1,OB,OP),OP=0;}

int n, p;
long long dp[10001];
int main(){
	while((n = R()) != 0){
		p = R(), dp[0] = 1;
		for(int i = 1; i <= p; ++i) dp[i] = 0;
		for(int a; n; --n){
			a = R();
			for(int j = 0; j + a <= p; ++j)
				dp[j+a] += dp[j];
		}
		W(dp[p]);
	}
	write(1,OB,OP);
}