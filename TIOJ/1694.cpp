// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
#define AI(x) x.begin(),x.end()
#define FOR(i,n) for(int i = 0; i < (n); ++i)
#define FOO(i,a,b) for(int i = (a); i <= (b); ++i)

const int N = 23225, Q = 2e5 + 225;
int n, q, h[N], l[Q], r[Q];
// range fenwick tree
short val[N];
inline void add(int p, int v){ for(; p < N; p += p & -p) val[p] += v;}
inline int query(int p){ int ans = 0; for(; p > 0; p -= p & -p) ans += val[p]; return ans;}
vector<int> bucket[500];
int main(){
	n = R(), q = R(); FOO(i,1,n) h[i] = R();
	FOR(i,q) l[i] = R(), r[i] = R(), bucket[l[i] >> 6].push_back(i);
	int ans = 0, cul = 1, cur = 1;
	add(h[1], 1);
	auto addl = [&ans](int p){
		ans += query(h[p] - 1);
		add(h[p], 1);
	};
	auto addr = [&ans](int p){
		ans += query(N - 1) - query(h[p]);
		add(h[p], 1);
	};
	auto subl = [&ans](int p){
		ans -= query(h[p] - 1);
		add(h[p], -1);
	};
	auto subr = [&ans](int p){
		ans -= query(N - 1) - query(h[p]);
		add(h[p], -1);
	};
	FOR(i,N>>6){
		if(bucket[i].empty()) continue;
		sort(AI(bucket[i]), [](int a, int b){ return r[a] < r[b];});
		if(i&1) reverse(AI(bucket[i]));
		for(int j: bucket[i]){
			while(cul > l[j]) addl(--cul);
			while(cur < r[j]) addr(++cur);
			while(cul < l[j]) subl(cul++);
			while(cur > r[j]) subr(cur--);
			l[j] = ans;
		}
	}
	FOR(i,q) W(l[i]);
	write(1,OB,OP);
	return 0;
}