#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<17;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while(c<'-') c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

// equal == 0 and less % 2 == 0

#include<algorithm>
using namespace std;
const int N = 1e5+1;
int n, m, a[N], b[N];

int main(){
	n = R(), m = R();
	FOR(i, n) a[i] = R();
	FOR(i, m) b[i] = R();

	sort(b, b + m);

	int ans = 0;
	FOR(i, n){
		int p = lower_bound(b, b + m, a[i]) - b;
		ans += p % 2 == 0 and b[p] != a[i];
	}
	printf("%d", ans);
}