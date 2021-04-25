// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

int main(){
	int k, a, dp0, dp1;
	while(k = R()){
		a = R();
		dp0 = a * 2 - 1;
		dp1 = a;
		for(int i = 2; i <= k; ++i){
			a = R();
			if(a == 1) dp0 = dp1 * 2 + a;
			else dp0 = dp1 * 2 + dp0 + a * 2;
			dp1 = dp1 * 2 + a;
		}
		W(dp0);
	}
	write(1,OB,OP);
	return 0;
}