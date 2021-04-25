#pragma GCC optimize("Os")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int N = 1e4 + 225;
int n, k;
char a[N], b[N], perm[N];

inline int get(int a, int perm){ return ((a + perm) % 9 + 9) % 9;}
inline int dis(int a, int b){ return a <= b ? b - a : 9 + b - a;}

int main(){
	n = R(), k = R();
	for(int i = 0; i < n; ++i) a[i] = R() - 1;
	for(int i = 0; i < n; ++i) b[i] = R() - 1;

	int i = 0, cur = 0, ans = 0, d;
	for(; i + k - 1 < n; ++i){
		cur += perm[i], d = dis(get(a[i], cur), b[i]);
		ans += d, cur += d, perm[i + k] -= d;
	}
	for(; i < n; ++i){
		cur += perm[i];
		if(get(a[i], cur) != b[i]){ W(0); return 0;}
	}
	W(ans);
	return 0;
}