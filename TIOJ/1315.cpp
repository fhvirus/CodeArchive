#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
typedef long long ll;
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline ll R(){
	ll ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
bool eek(__int128 a, __int128 b, __int128 c){
	return a > 0 and b > 0 and c > 0 and
		   (a*a == b*b+c*c or
			b*b == a*a+c*c or
			c*c == a*a+b*b);
}

int main(){
	ll n, a, b, c;
	n = R();
	FOR(i,n){
		a = R(), b = R(), c = R();
		puts(eek(a, b, c) ? "yes" : "no");
	}
}