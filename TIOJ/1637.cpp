#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int SZ = 1<<20;
inline char readchar(){
	static char buf[SZ], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,SZ,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

const int N = 1e6;
int n, a[N];
long long ans;
int S[N], I[N], L[N], p;

int main(){
	n = R();
	FOR(i, n-1){
		a[i] = R();
		while(p > 0 and S[p-1] <= a[i]) --p;
		L[i] = p == 0 ? -1 : I[p-1];
		S[p] = a[i], I[p] = i, ++p;
	}
	p = 0;
	for(int i = n-2; i >= 0; --i){
		while(p > 0 and S[p-1] < a[i]) --p;
		ans += 1ll * a[i] * ((p == 0 ? n-1 : I[p-1]) - i) * (i - L[i]);
		S[p] = a[i], I[p] = i, ++p;
	}
	printf("%lld\n", ans);
}