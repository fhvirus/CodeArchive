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

#include<algorithm>
#include<cmath>
using namespace std;
const int N = 1e5;
int n, a[N];
long long ans, ans2, jizz;

int main(){
	n = R();
	FOR(i, n) a[i] = R();
	std::sort(a, a + n);
	if(n <= 2){printf("%d\n", a[0] - 1); return 0;}
	for(int i = 0; i < n; ++i) jizz += a[i] - 1;
	if(n >= 30){ printf("%lld\n", jizz); return 0;}
	int root = ceil(pow(a[n-1], 1.0/(n-1))), rrot = floor((pow(a[n-1], 1.0/(n-1))));
	// printf("%d\n", rrot);
	for(int i = 0; i < n; ++i) ans += abs(a[i] - pow(root, i));
	for(int i = 0; i < n; ++i) ans2 += abs(a[i] - pow(rrot, i));
	printf("%lld\n", min(ans, ans2));
}