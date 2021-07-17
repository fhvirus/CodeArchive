// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
#include<algorithm>
using namespace std;
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n, char e){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}

const int kN = 1000;

int n, a[kN];

signed main(){
	n = R();
	for(int i = 0; i < n; ++i) a[i] = R();
	// why stable sort is so fat
	stable_sort(a, a + n, [](int a, int b){ return __builtin_popcount(a) < __builtin_popcount(b); });
	for(int i = 0; i < n; ++i) W(a[i], ' ');
	write(1,OB,OP);
	return 0;
}
