#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#define max(a,b) (a>b?a:b)

const int N = 10000;
struct stone{
	int w, m;
} s[500];
int p;
int dp[N+1];

signed main(){
	int n, t;
	n = R();
	for(int i = 0, w, m, c; i < n; ++i){
		w = R(), m = R(), c = R();
		for(int j = 1; j <= c; c -= j, j<<=1)
			s[p++] = {w*j, m*j};
		if(c) s[p++] = {w*c, m*c};
	}
	t = R();
	for(int i = 0; i < p; ++i){
		for(int j = t; j >= s[i].w; --j)
			dp[j] = max(dp[j], dp[j - s[i].w] + s[i].m);
	}
	int ans = 0;
	for(int i = 0; i <= t; ++i)
		ans = max(ans, dp[i]);
	W(ans);
}