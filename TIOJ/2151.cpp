//Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline long long R(){static char c;long long a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#define ll long long
#define FOR(i,n) for(int i = 0; i < (n); ++i)
#define max(a,b) (a>b?a:b)

const int N = 225;
const ll INF = 1e18;
ll n, m, s, t, c[N];
ll a[N][N], b[N][N], ans[N][N];
int main(){
	n = R(), m = R(), s = R(), t = R();
	FOR(i,n) c[i] = R();
	FOR(i,n) FOR(j,n) ans[i][j] = -INF;
	FOR(i,n) FOR(j,n) a[i][j] = -INF;
	ans[s-1][s-1] = 0;
	for(int u, v; m; --m){
		u = R() - 1, v = R() - 1;
		a[u][v] = c[v];
	}
	while(t){
		if(t & 1){
			FOR(i,n) FOR(j,n) {
				b[i][j] = -INF;
				FOR(k,n) b[i][j] = max(b[i][j], ans[i][k] + a[k][j]);
			}
			FOR(i,n) FOR(j,n) ans[i][j] = b[i][j];
		}
		FOR(i,n) FOR(j,n){
			b[i][j] = -INF;
			FOR(k,n) b[i][j] = max(b[i][j], a[i][k] + a[k][j]);
		}
		FOR(i,n) FOR(j,n) a[i][j] = b[i][j];
		t >>= 1;
	}
	ll eek = ans[s-1][0];
	FOR(i,n) eek = max(eek, ans[s-1][i]);
	W(eek);
	return 0;
}