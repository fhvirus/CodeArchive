// Knapsack DP is harder than FFT.
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}


#pragma GCC optimize("Ofast")
#include<vector>
#include<algorithm>
using namespace std;
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 

const int N = 2e4 + 225, M = 1e9 + 7;
int n, k, a[N];

struct LISAN : vector<int>{
	inline void done(){ sort(AI()), erase(unique(AI()), end());}
	int operator()(int i){ return lower_bound(AI(), i) - begin();}
} lis;
int v[N];
void init(){ fill(v, v + n + 2, 0);}
inline void add(int p, int val){ for( ++p; p < n + 2; p += p & -p) v[p] += val;}
inline int query(int p){
	int r = 0;
	for( ++p; p > 0; p -= p & -p) r += v[p];
	return r;
}

bool check(int m){
	init();
	int cnt = 0;

	vector<int> ls(n + 1);
	int p = 0;
	FOO(i,0,n){
		while(p <= n and lis[i] - lis[p] >= m) ++p;
		ls[i] = p;
	}

	FOO(i,0,n){
		cnt += query(ls[a[i]]);
		add(a[i] + 1, 1);
	}
	return cnt >= k;
}

void solve(){
	int mx = 0, mn = 0, lo = 0, hi = 0;
	lis = LISAN();
	lis.pb(0);
	FOO(i,1,n){
		a[i] = R() + a[i-1];
		lis.pb(a[i]);
		chmin(lo, a[i] - mx);
		chmax(hi, a[i] - mn);
		chmin(mn, a[i]);
		chmax(mx, a[i]);
	}
	lis.done(); FOO(i,0,n) a[i] = lis(a[i]);

	int ans = lo;
	for(int l = 1<<28; l > 0; l >>= 1)
		if(ans + l <= hi and check(ans + l)) ans += l;
	W(ans);
}

int32_t main(){
	while((n = R()) && (k = R())) solve();
	write(1,OB,OP);
	return 0;
}

