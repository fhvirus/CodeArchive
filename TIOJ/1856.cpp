#pragma Ofast
#pragma loop_opt(on)
#pragma GCC target("avx,avx2")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}


#include<algorithm>
const int N = 1e5;
int T, n, a[N];
long long ans;

int main(){
	T = R();
	for(;T;--T){
		ans = 0;
		n = R();
		for(int i = 0; i < n; ++i) a[i] = R();
		std::sort(a, a + n, [](int a, int b){return a > b;});
		int i;
		for(i = 0; i < n and a[i] > i+1; ++i) ans += a[i];
		ans -= (1 + i) * i / 2;
		W(ans);
	}
	write(1,OB,OP);
	return 0;
}