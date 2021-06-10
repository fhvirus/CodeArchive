#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline long long R(){static char c;long long a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

const int N = 1e6 + 1;
int n, q;
long long h[N];

int main(){
	n = R(); q = R();
	for(int i = 1; i <= n; ++i) h[i] = R() ^ h[i-1];
	for(; q; --q) W(h[R()-1] ^ h[R()]);
	write(1,OB,OP);
}