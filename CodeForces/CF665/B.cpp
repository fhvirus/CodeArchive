#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
inline int min(int a, int b){
	return a < b ? a : b;
}

int t, a, b, c, d, e, f, eek;
long long ans;

int main(){
	t = R();
	for(; t; --t){
		ans = 0;
		c = R(), b = R(), a = R(), f = R(), e = R(), d = R();

		eek = min(a, e);
		ans += eek * 2; a -= eek; e -= eek;

		eek = min(d, c);
		d -= eek; c -= eek;

		eek = min(d, a);
		d -= eek; a -= eek;

		eek = min(d, b);
		ans -= 2 * eek; d -= eek; b -= eek;
		
		printf("%lld\n", ans);
	}
}