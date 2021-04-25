// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<algorithm>
#include<utility>
using namespace std;

typedef long long ll;
#define ff first
#define ss second

const int N = 1e5 + 225;
int n, id[N], uc[N], lc[N], up, lp;
using pll = pair<ll, ll>;
pll operator-(const pll &l, const pll &r){ return {l.ff - r.ff, l.ss - r.ss};}
inline ll crs(const pll &a, const pll &b){ return a.ff * b.ss - a.ss * b.ff;}
pll p[N];

int32_t main(){
	n = R();
	for(int i = 0; i < n; ++i) p[i] = {R(), R()}, id[i] = i;
	sort(id, id + n, [](int a, int b){ return p[a] < p[b];});

	uc[up++] = id[0], lc[lp++] = id[0];
	for(int i = 1; i < n; ++i){
		{	// upper convex
			pll a, b, c = p[id[i]];
			while(up > 1){
				a = p[uc[up - 2]];
				b = p[uc[up - 1]];
				if(crs(c - a, b - a) < 0) break;
				--up;
			}
			uc[up++] = id[i];
		}
		{	// lower convex
			pll a, b, c = p[id[i]];
			while(lp > 1){
				a = p[lc[lp - 2]];
				b = p[lc[lp - 1]];
				if(crs(c - a, b - a) > 0) break;
				--lp;
			}
			lc[lp++] = id[i];
		}
	}
	for(int i = 0; i < lp; ++i) uc[up++] = lc[i];
	sort(uc, uc + up);
	up = unique(uc, uc + up) - uc;

	W(up);
	for(int i = 0; i < up; ++i) W(uc[i] + 1);
	write(1,OB,OP);
	return 0;
}
