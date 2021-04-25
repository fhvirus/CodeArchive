#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[1<<17]; int OP;
inline char RC(){static char buf[1<<17],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,1<<17))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>131052)write(1,OB,OP),OP=0;}

const int M = 1e9 + 7;

int main(){
	for(int t = R(), n; t; --t){
		n = (R() - 1);
		long long ans = 1, x = 4;
		while(n) (n&1) && (ans = ans * x % M), x = x * x % M, n >>= 1;
		W(ans);
	}
	write(1, OB, OP);
}