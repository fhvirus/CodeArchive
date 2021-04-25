#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
using namespace std;

const int N = 1001;
int n;
short x[N*N], y[N*N];

/* BIT */
int bit[N][N];
inline void modify(int x, int y, int v){
	for(int i = x; i <= n; i += i & -i)
		for(int j = y; j <= n; j += j & -j)
			bit[i][j] = max(bit[i][j], v);
}
inline int query(int x, int y){
	int ans = 0;
	for(int i = x; i > 0; i -= i & -i)
		for(int j = y; j > 0; j -= j & -j)
			ans = max(ans, bit[i][j]);
	return ans;
}
/* BIT */

int main(){
	n = R();
	for(int i = 1, v; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			v = R(), x[v] = i, y[v] = j;

	for(int i = 1; i <= n * n; ++i)
		modify(x[i], y[i], query(x[i], y[i]) + 1);
	W(query(n, n));
	return 0;
}