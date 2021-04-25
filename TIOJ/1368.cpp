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

const int N = 1e5+1;
long long sum[N], ans;
int a[N], ansl, ansr;
int n, l[N], r[N];
int stck[N], top;
inline long long max(long long a, long long b){
	return a > b ? a : b;
}

int main(){
	while((n = R()) != 0){
		for(int i = 1; i <= n; ++i)
			a[i] = R(), sum[i] = sum[i-1] + a[i];
		top = 0;
		for(int i = 1; i <= n; ++i){
			while(top > 0 and a[stck[top-1]] >= a[i]) --top;
			l[i] = top > 0 ? stck[top-1] : 0;
			stck[top++] = i;
		}
		top = 0;
		for(int i = n; i > 0; --i){
			while(top > 0 and a[stck[top-1]] >= a[i]) --top;
			r[i] = top > 0 ? stck[top-1] - 1 : n;
			stck[top++] = i;
		}
		ans = 0, ansl = 0, ansr = 0;
		for(int i = 1; i <= n; ++i)
			if(ans < (sum[r[i]] - sum[l[i]]) * a[i]){
				ans = (sum[r[i]] - sum[l[i]]) * a[i],
				ansl = l[i] + 1,
				ansr = r[i];
			}
		printf("%lld\n%d %d\n", ans, ansl, ansr);
	}
}