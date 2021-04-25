#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
using namespace std;

const int N = 1001;
int n, l, p[N];
int dpl[2][N], dpr[2][N];

int main(){
	n = R(), l = R();
	for(int i = 0; i < n; ++i)
		p[i] = R();
	sort(p, p + n);

	for(int i = 0; i < n; ++i)
		dpl[0][i] = dpr[0][i] = abs(l - p[i]) * n;

	int roll = 1;
	for(int len = 1; len < n; ++len){
		for(int l = 0; l + len < n; ++l){
			dpl[roll][l] = min(
				dpl[1 - roll][l + 1] + (p[l + 1] - p[l]) * (n - len),
				dpr[1 - roll][l + 1] + (p[l + len] - p[l]) * (n - len)
			);
			dpr[roll][l] = min(
				dpl[1 - roll][l] + (p[l + len] - p[l]) * (n - len),
				dpr[1 - roll][l] + (p[l + len] - p[l + len - 1]) * (n - len)
			);
		}
		roll = 1 - roll;
	}
	W(min(dpl[1 - roll][0], dpr[1 - roll][0]));

	return 0;
}