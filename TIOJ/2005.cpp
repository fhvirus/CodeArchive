#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

inline int log10(int n){
	return (n >= 10000 ? (n >= 1000000 ? (n >= 10000000 ? (n >= 100000000 ? 100000000 : 10000000) : 1000000) : (n >= 100000 ? 100000 : 10000)) : (n >= 100 ? (n >= 1000 ? 1000 : 100) : (n >= 10 ? 10 : 1))) * 10;
}
long long n, m, ans;

int main(){
	while(true){
		n = R(), m = R();
		if(n == 0) break;
		ans = 0;
		for(int i = 1; i <= n; ++i){
			ans = (ans*log10(i)%m + (i % m));
		}
		printf("%lld\n", ans % m);
	}
}