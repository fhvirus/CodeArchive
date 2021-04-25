// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

typedef long long ll;
#define FOR(i,n) for(int i=0;i<(n);++i)
template<class I> I max(I a, I b){ return a > b ? a : b;}
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
constexpr inline ll cdiv(ll x,ll m){return x/m+(x%m?(x<0)^(m>0):0);}

const int N = 1000;
ll a[N], b[N];
void solve(int n){
	ll k, m, ans = 0, lft = 0, sum = 0;

	FOR(i,n) b[i] = R(), sum += b[i];
	k = R();
	FOR(i,n) a[i] = R(), chmax(ans, cdiv(a[i], b[i]));
	m = R();

	FOR(i,n) lft += b[i] * ans - a[i];
	
	W(ans + max((ll)0, cdiv(m * k - lft, sum)));
	return;
}
int main(){
	int n;
	while((n = R()) != 0){
		solve(n);
	}
	write(1,OB,OP);
	return 0;
}