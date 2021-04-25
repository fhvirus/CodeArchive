#pragma GCC optimize("Os")
#include<unistd.h>
inline char RC(){static char buf[50],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,50))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const long long M = 1e6;
long long a, b, c, d;
inline long long p(long long x, int e){
	int ans = 1;
	while(e) (e&1)&&(ans=ans*x%M), x=x*x%M, e>>=1;
	return ans;
}
int main(){
	a = R(), b = R(), c = R(), d = R();
	int ans = 0;
	for(; a <= d; a += b)
		ans = (ans + p(a, c))%M;
	W(ans);
}