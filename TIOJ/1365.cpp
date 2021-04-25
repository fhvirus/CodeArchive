// Knapsack DP is harder than FFT.
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';return a;}
inline void W(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}
#define FOR(i,n) for(int i=0;i<n;++i)
#include<algorithm>
#include<utility>
using namespace std;
const int N = 1e6 + 225;
int n;
pair<int,int> c[N];

struct BIT{
	int v[N];
	void init(){
		fill(v, v + N, 0);
	}
	void add(int p){
		for(; p; p -= p & -p) v[p]++;
	}
	int que(int p){
		int ans = 0;
		for(; p < N; p += p & -p) ans += v[p];
		return ans;
	}
} bit;

int32_t main(){
	while(n = R()){
		FOR(i,n) c[i].first = R(), c[i].second = R();
		sort(c, c + n);
		bit.init();
		long long ans = 0;
		FOR(i,n){
		   	ans += bit.que(c[i].second + 1);
			bit.add(c[i].second);
		}
		W(ans);
	}
	write(1,OB,OP);
	return 0;
}
