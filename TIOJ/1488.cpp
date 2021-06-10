// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)
#include<unistd.h>
char OB[225]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';}
typedef long long ll;

const int N = 901;
const ll INF = 1e18;

int n;
ll dp[N][N];
int a[N];
ll tot;

void solve(){
	n = R();
	for(int i = 0; i < n; ++i) a[i] = R(), a[i+1] = R();

	for(int r = 1; r < n; ++r){
		for(int l = r - 1; l >= 0; --l){
			ll cur = INF, tmp, eek = a[l] * a[r+1];
			for(int k = l; k < r; ++k){
				tmp = dp[l][k] + dp[k+1][r] + eek * a[k+1];
				if(tmp < cur) cur = tmp;
			}
			dp[l][r] = cur;
		}
	}

	tot += dp[0][n-1];
	W((dp[0][n-1] + 999) / 1000);
}

signed main(){
	for(int t = R(); t; --t) solve();
	W((tot + 999) / 1000);
	write(1,OB,OP);
	return 0;
}
