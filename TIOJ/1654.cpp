#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int N = 1e6 + 1;
#define max(a,b) (a>b?a:b)
int n, m, par[N], lvl[N], ans;

int main(){
	n = R(), m = R();
	for(int i = 2; i <= n; ++i) par[i] = R();
	for(int i = n; i >= 1; --i){
		lvl[par[i]] = max(lvl[par[i]], lvl[i] + 1);
		ans += (lvl[i] < m);
	}
	W(ans);
}