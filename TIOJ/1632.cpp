#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline long long RL(){static char c;long long a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
using namespace std;
const int N = 2e5;
int n, a[N];
long long k;

int main(){
	n = R(), k = RL();
	for(int i = 0; i < n; ++i)
		a[i] = R();
	sort(a, a + n);

	long long l = 0, r = 1, len, ans;
	while(r * (r - 1) / 2 < k) ++r;
	r = a[r] - a[0];

	while(l < r){
		len = (l + r) / 2;
		ans = 0;
		for(int lptr = 0, rptr = 0; ans < k and lptr < n; ++lptr){
			while(rptr < n and a[rptr] - a[lptr] <= len) ++rptr;
			--rptr;
			ans += rptr - lptr;
		}
		(ans >= k) ? r = len : l = len + 1;
	}
	W(l);
	return 0;
}