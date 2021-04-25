#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

const int N = 15;
int n, val[N][N], eek[N][N];
int dp[1<<N];

#define FOR(i,n) for(int i=0;i<n;++i)
inline int max(int a, int b){ return a > b ? a : b;}

int main(){
	while((n = R()) != 0){
		FOR(i,n)FOR(j,n) val[i][j] = R();
		FOR(i,n)FOR(j,n) eek[i][j] = R();
		FOR(d,1<<n){
			dp[d] = 0;
			if((d & (d-1)) == 0) continue;
			FOR(i,n){
				if((d & (1<<i)) == 0) continue;
				for(int j = i + 1; j < n; ++j)
					if(d & (1<<j)) dp[d] = max(
						dp[d],
						dp[d ^ (1<<i) ^ (1<<j) ^ (1<<eek[i][j])] + val[i][j]
					);
			}
		}
		W(dp[(1<<n)-1]);
	}
	write(1,OB,OP);
	return 0;
}