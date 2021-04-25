#pragma GCC optimize("Ofast")
typedef long long ll;
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(ll n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

inline ll abs(ll a){ return a < 0 ? -a : a;}
inline ll min(ll a, ll b){ return a < b ? a : b;}

int main(){
	int T, n, i;
	ll a, a1, a2, dp, dp1, dp2;
	T = R();
	for(; T; --T){
		n = R();
		a2 = R(), a1 = R();
		dp2 = 0, dp1 = abs(a1 - a2);
		for(i = 2; i < n; ++i){
			a = R();
			dp = min(dp1 + abs(a1 - a), dp2 + abs(a2 - a));
			a2 = a1; a1 = a;
			dp2 = dp1; dp1 = dp;
		}
		W(dp1);
	}
	write(1,OB,OP);
}