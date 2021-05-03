// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
typedef long long ll;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline ll R(){static char c;ll a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(ll n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int N = 500;

int n;
ll a[N][N], b[N];

int main(){
	n = R();
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) a[i][j] = R();

	ll ans = 0, sum = 0;
	for(int i = 0; i < n; ++i){
		for(int k = 0; k < n; ++k) b[k] = 0;
		for(int j = i; j < n; ++j){
			sum = 0;
			for(int k = 0; k < n; ++k){
				b[k] += a[j][k];
				sum += b[k];
				if(sum < 0) sum = 0;
				if(ans < sum) ans = sum;
			}
		}
	}
	W(ans);
	return 0;
}