// Knapsack DP is harder than FFT.
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}


#pragma GCC optimize("Ofast")
#include<algorithm>
using namespace std;
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 

const int N = 2e4 + 225, M = 1e9 + 7;
int n, k, a[N];

int s[N], t[N];
int gueibing(int l, int r, int v){
	//debug(l, r, v);
	if(l + 1 >= r) return 0;
	if(r - l < 150){
		int ans = 0;
		FOO(i,l,r-1) FOO(j,l,i-1) ans += (s[i] - s[j] >= v);
		sort(s + l, s + r);
		return ans;
	}
	int m = (l + r) / 2;
	int ans = gueibing(l, m, v) + gueibing(m, r, v);
	int p = m;
	FOO(i,l,m-1){
		while(p < r and s[p] - s[i] < v) t[p] = s[p], ++p;
		ans += r - p;
		t[i] = s[i];
	}
	for(; p < r; ++p) t[p] = s[p];
	merge(t+l, t+m, t+m, t+r, s+l);
	return ans;
}

bool check(int v){
	FOO(i,0,n) s[i] = a[i];
	return gueibing(0, n + 1, v) >= k;
}

void solve(){
	FOO(i,1,n) a[i] = R() + a[i-1];

	int mx = 0, mn = 0, lo = 0, hi = 0;
	FOO(i,1,n){
		chmin(lo, a[i] - mx);
		chmax(hi, a[i] - mn);
		chmin(mn, a[i]);
		chmax(mx, a[i]);
	}

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
