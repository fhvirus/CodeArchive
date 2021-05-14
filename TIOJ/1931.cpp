#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

#include<algorithm>
const int N = 1e5+1;
unsigned t, n, a[N];
long long F, B[N+2], ans;

int main(){
	t = R();
	for(; t; --t){
		n = R(); ans = 0;
		FOR(i,n) a[i] = R();
		std::sort(a+1, a+1 + n);
		if(n % 2 == 0){
			for(int i = 1; i <= n; i += 2) ans += (a[i]<<2);
		} else {
			for(int i = n-1; i > 0; i -= 2){
				B[i] = B[i + 2] + (a[i]<<2);
			}
			F = 0;
			for(int i = 1; i <= n; i += 2){
				ans = std::max(ans, F + B[i + 1]);
				F += a[i-1]<<2;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
