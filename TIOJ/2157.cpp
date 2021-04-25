#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
const int N = 5e5, M = 998244353;
int n, a[N];
int main(){
	n = R();
	for(int i = 0; i < n; ++i)
		a[i] = R();
	std::sort(a, a + n);
	int ans = 0, e = 1;
	for(int i = 0; i < n; ++i){
		ans += (long long)a[i] * e % M;
		e = e * 2 % M;
		ans %= M;
	}
	W(ans);
}