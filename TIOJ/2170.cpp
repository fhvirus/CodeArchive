#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
#include<algorithm>
using namespace std;
const int N = 101;
int n, m, p[N], a[N][N], ans[N];
inline void swapRow(int u, int v){
	swap(p[u], p[v]);
	for(int i = 0; i < n; ++i)
		swap(a[u][i], a[v][i]);
}
inline int mpow(unsigned x, int e){
	unsigned ans = 1;
	while(e) (e&1) and (ans = ans * x % m), x = x * x % m, e >>= 1;
	return ans;
}
inline int money(int x){
	return mpow(x, m-2);
}
inline int mmul(int u, int v){
	return (unsigned)u * v % m;
}
signed main(){
	n = R(), m = R();
	FOR(i, n) p[i] = R();
	FOR(i, n) FOR(j, n) a[j][i] = R();
	
	// Gauss
	FOR(k, n){
		for(int i = k; i < n; ++i)
			if(a[i][k] != 0){
				swapRow(i, k);
				break;
			}

		int jizz = money(a[k][k]);
		for(int i = k; i < n; ++i)
			a[k][i] = mmul(a[k][i], jizz);
		p[k] = mmul(p[k], jizz);

		for(int r = k + 1; r < n; ++r){
			for(int i = k + 1; i < n; ++i)
				a[r][i] -= mmul(a[r][k], a[k][i]), a[r][i] += a[r][i] < 0 ? m : 0;
			p[r] -= mmul(p[k], a[r][k]), p[r] += p[r] < 0 ? m : 0;
			a[r][k] = 0;
		}
	}
	

	for(int k = n-1; k >= 0; --k){
		ans[k] = p[k];
		for(int i = k + 1; i < n; ++i)
			ans[k] = (ans[k] - mmul(ans[i], a[k][i]) + m) % m;
	}

	FOR(i, n) printf("%d ", ans[i]);
}