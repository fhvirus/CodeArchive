// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[44444],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,44444))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
using namespace std;
#define FOR(i,n) for(int i = 0; i < (n); ++i)
#define FOO(i,a,b) for(int i = (a); i <= (b); ++i)
template<typename I> bool chmax(I &a, I b){ return a < b ? (a = b, true) : false;}
template<typename I> bool chmin(I &a, I b){ return a > b ? (a = b, true) : false;}

const int N = 3e5 + 225;
int n, a[N], b;
int sum;
struct point{
	int x, y, w;
	point(){}
	point(int x, int y, int w): x(x), y(y), w(w){}
} P[N];
const inline bool cmp(point a, point b){
	return 1ll * a.x * b.y > 1ll * a.y * b.x;
}
const inline bool sam(point a, point b){
	return 1ll * a.x * b.y == 1ll * a.y * b.x;
}

int main(){
	n = R();
	FOR(i,n){
		int x, y, w; x = R(), y = R(), w = R();
		if(x < 0 or (x == 0 and y < 0)) x = -x, y = -y;
		P[i] = point(x, y, w);
		sum += w;
	}
	sort(P, P + n, cmp);
	FOR(i,n){
		int eek = 0, j = i;
		for(; j < n; ++j){
			if(!sam(P[i], P[j])) break;
			eek += P[j].w;
		}
		i = j - 1;
		a[b++] = eek;
	}

	int ans = -1e9;
	int mx = 0, mn = 0;
	FOR(i,b){
		chmax(mx, 0);
		chmin(mn, 0);
		mx += a[i];
		mn += a[i];
		chmax(ans, mx);
		chmax(ans, sum - mn);
	}

	W(ans);
	
	return 0;
}