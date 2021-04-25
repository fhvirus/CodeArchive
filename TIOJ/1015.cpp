#pragma GCC optimize("Ofast")
#define ull unsigned long long
#include<unistd.h>
char OB[2048]; int OP;
inline char RC(){static char buf[2048],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,2048))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(ull n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>2028)write(1,OB,OP),OP=0;}


unsigned long long n, m, a, b;
int main(){
	while(true){
		n = R(); m = R();
		if(n == 0) break;
		a = n < m ? n : m; b = n + m - a;
		W(((3 * b - a + 1) * a * (a + 1)) / 6);
	}
	write(1,OB,OP);
}