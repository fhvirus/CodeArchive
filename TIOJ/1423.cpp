// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}


#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)

const int N = 350;
int n, x[N], y[N];

int main(){
	n = R();
	FOR(i,n) x[i] = R(), y[i] = R();
	long long ans = 0;
	FOR(i,n){
		FOO(j,i+1,n-1){
			int a = y[j] - y[i];
			int b = -(x[j] - x[i]);
			long long u = 0, d = 0;
			FOR(k,n){
				int r = a * (x[k] - x[i]) + b * (y[k] - y[i]);
				if(r > 0) ++u;
				if(r < 0) ++d;
			}
			ans += u * d;
		}
	}
	W(ans);
	return 0;
}
