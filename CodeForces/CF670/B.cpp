#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

const int N = 2e5;
int t, n;
long long a[N], mndp[5][N], mxdp[5][N];

#include<algorithm>
using namespace std;

int main(){
	t = R();
	for(; t; --t){
		n = R();
		FOR(i, n) a[i] = mndp[0][i] = mxdp[0][i] = R();
		for(int k = 1; k < 5; ++k){
			long long mx = mxdp[k-1][k-1], mn = mndp[k-1][k-1];
			for(int i = k; i < n; ++i){
				mxdp[k][i] = (a[i] < 0 ? mn : mx) * a[i];
				mndp[k][i] = (a[i] < 0 ? mx : mn) * a[i];
				mx = max(mx, mxdp[k-1][i]), mn = min(mn, mndp[k-1][i]);
			}
		}
		long long ans = -1e18;
		for(int i = 4; i < n; ++i) ans = max(ans, mxdp[4][i]);
		printf("%lld\n", ans);
	}
	return 0;
}