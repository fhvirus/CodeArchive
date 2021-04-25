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

const int N = 1e5;
int n;
long long a[N];

int main(){
	n = R();
	FOR(i, n) a[i] = R();
	if(n == 1){
		puts("1 1");
		printf("%lld\n", -a[0]);
		puts("1 1\n0\n1 1\n0");
		return 0;
	}

	puts("1 1");
	printf("%lld\n", n - a[0]);
	a[0] = n;

	printf("2 %d\n", n);
	for(int i = 1; i < n; ++i){
		long long jizz = a[i] * (n-1);
		printf("%lld ", jizz);
		a[i] += jizz;
	}
	puts("");

	printf("1 %d\n", n);
	for(int i = 0; i < n; ++i)
		printf("%lld ", -a[i]);
}