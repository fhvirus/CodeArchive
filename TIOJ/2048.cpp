#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
typedef long long int ll;
inline char readchar(){
	const int S = 1<<20;
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
const int MAXN = 1e6;
const ll LLONG_MIN = -1e18;
inline ll max(ll a, ll b){
	return a > b ? a : b;
}

int a;
ll b[4], c[2];

int main(){
	int n = R();
	c[0] = c[1] = LLONG_MIN;

	b[0] = R();

	a = R();
	b[1] = max(a, max(b[0], b[0] + a));

	ll ans = LLONG_MIN;
	for(int i = 2; i < n; ++i){
		a = R();
		b[i&3] = max(a, max(b[(i-1)&3], b[(i-1)&3] + a));
		c[i&1] = max(c[(i&1)^1], b[(i-2)&3]) + a;
		ans = max(ans, c[i&1]);
	}

	printf("%lld\n", ans);
	
	return 0;
}