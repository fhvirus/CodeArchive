#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

inline short min(short a, short b){ return a < b ? a : b;}

const int N = 21;
const short INF = 32767;
#include<algorithm>
int t, n;
short a[N][N];
short dp[1<<N];
int tmp[N], p;

inline void solve(){
	n = R();
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			a[i][j] = R();

	std::fill(dp, dp + (1<<n), INF);
	dp[0] = 0;

	for(int d = 0; d < (1<<n); ++d) if(dp[d] < INF){
		p = 0;
		for(int i = 0; i < n; ++i)
			if((d & (1<<i)) == 0) tmp[p++] = i;

		int i = tmp[--p];
		for(int j = 1; j < p; ++j){
			for(int k = 0; k < j; ++k){
				dp[d | (1<<i) | (1<<tmp[j]) | (1<<tmp[k])] = min(
					dp[d | (1<<i) | (1<<tmp[j]) | (1<<tmp[k])],
					dp[d] + a[i][tmp[j]] + a[tmp[j]][tmp[k]] + a[tmp[k]][i]
				);
			}
		}
	}
	W(dp[(1<<n) - 1]);
}

int main(){
	for(t = R(); t; --t)
		solve();
	write(1,OB,OP);
	return 0;
}