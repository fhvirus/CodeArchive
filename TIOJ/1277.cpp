#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar(); bool minus = false;
	while(c<'-') c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
#define int long long
bool owo = true;
int n, a[501][501], eek[501], ans, in, sum;
signed main(){
	n = R();
	FOR(i, n) FOR(j, n) in = R(), a[i][j] = in + a[i-1][j], owo &= in >= 0, sum += in;
	if(owo){ printf("%lld", sum); return 0;}
	for(int u = 0; u < n; ++u){
		for(int d = u + 1; d <= n; ++d){
			int jizz = 0;
			FOR(i, n) jizz += a[d][i] - a[u][i], ans = ans > jizz ? ans : jizz, (jizz < 0) and (jizz = 0);
		}
	}
	printf("%lld\n", ans);
}