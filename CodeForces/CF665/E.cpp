#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

const int N = 1e5+3;
int n, m;

struct HOR{
	int y, lx, rx;
	HOR(){};
} H[N];
struct VER{
	int x, ly, ry;
	VER(){}
} U[N], D[N];

int u, d;

const int MAXN = 1e6+1;
struct BIT{
	int val[MAXN+2];
	void insert(int p){
		while(p <= MAXN) val[p]++, p += (p & -p);
	}
	void remove(int p){
		while(p <= MAXN) val[p]--, p += (p & -p);
	}
	int query(int p){
		int ans = 0;
		while(p > 0) ans += val[p], p -= (p & -p);
		return ans;
	}
	int query(int l, int r){
		return query(r) - query(l-1);
	}
} bit;

#include<algorithm>
using namespace std;

int main(){
	n = R(), m = R();
	FOR(i,n){ H[i].y = R(); H[i].lx = R(); H[i].rx = R();}
	H[n].y = 0; H[n].lx = 0; H[n].rx = 1000000; ++n;
	H[n].y = 1000000; H[n].lx = 0; H[n].rx = 1000000; ++n;
	for(int i = 0, a, b, c; i < m; ++i){
		a = R(), b = R(), c = R();
		if(b == 0){ D[d].x = a, D[d].ry = c, ++d;}
		else if(c == 1000000){ U[u].x = a, U[u].ly = b, ++u;}
	}
	D[d].x = 0; D[d].ly = 0; D[d].ry = 1000000; ++d;
	D[d].x = 1000000; D[d].ly = 0; D[d].ry = 1000000; ++d;
	sort(H, H + n, [](HOR a, HOR b){ return a.y < b.y;});
	sort(U, U + u, [](VER a, VER b){ return a.ly < b.ly;});
	sort(D, D + d, [](VER a, VER b){ return a.ry < b.ry;});

	int uc = 0, dc = 0;
	long long ans = 0;
	FOR(i, d) bit.insert(D[i].x);
	FOR(i,n){
		// while(dc < d and D[dc].ry < H[i].y) bit.remove(D[dc].x), ++dc;
		// while(uc < u and U[uc].ly <= H[i].y) bit.insert(U[uc].x), ++uc;
		// FOR(j, i){
		// 	int l = max(H[i].lx, H[j].lx);
		// 	int r = min(H[i].rx, H[j].rx);
		// 	if(l >= r) continue;
		// 	ans += bit.query(l, r) - 1;
		// }
	}

	printf("%lld\n", ans);
}