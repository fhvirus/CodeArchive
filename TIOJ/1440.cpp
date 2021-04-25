#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<algorithm>
#define ll int64_t
#define MAXN 1000000
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q and (q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c = readchar();
	while(c>='0') ans=ans*10+(c^'0'), c=readchar();
	return ans;
}
struct breakfast{
	int b, c;
	bool operator<(const breakfast& rhs)const{
		return c < rhs.c;
	}
} B[MAXN];
ll n, m;
int A[MAXN];

int main(){
	n = R();
	for(int i = 0; i < n; ++i) A[i] = R();
	m = R();
	for(int i = 0; i < m; ++i)
		B[i].b = R(), B[i].c = R();
	std::sort(A, A+n);
	std::sort(B, B+m);
	ll ans = 0;
	for(int i = 0, ptr = 0; i < n; ++i){
		for(;B[ptr].b < A[i] and ptr < m;++ptr);
		if(ptr == m){
			puts("Impossible.");
			return 0;
		}
		ans += B[ptr++].c;
	}
	printf("%lld", ans);
	return 0;
}