#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[4096]; int OP;
inline char RC(){static char buf[4096],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,4096))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#define FOR(i,n) for(int i=0;i<n;++i)
#include<algorithm>
using namespace std;
const int N = 20000;
int n, w[N], l[N];
long long s, ans;
int main(){
	n = R();
	FOR(i, n) w[i] = R(); FOR(i, n-1) l[i] = R();
	sort(w, w + n); sort(l, l + n - 1);
	FOR(i, n-1){ s += w[i]; ans += s * l[n - i - 2];}
	W(ans);
}