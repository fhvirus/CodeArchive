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
int n, r[501], b[501];
long long ans;

int main(){
	while((n = R()) != 0){
		ans = 0;
		for(int i = 0; i <= 500; ++i) r[i] = b[i] = 0;
		for(int i = 0; i < n; ++i) ++r[R()];
		for(int i = 0; i < n; ++i) ++b[R()];
		int i = 500, j = 500, jizz;
		while(n > 0){
			while(i > 0 and r[i] == 0) --i;
			while(j > 0 and b[j] == 0) --j;
			jizz = std::min(r[i], b[j]);
			ans += 1ll * i * j * jizz, r[i] -= jizz, b[j] -= jizz, n -= jizz;
		}
		printf("%lld\n", ans);
	}
}