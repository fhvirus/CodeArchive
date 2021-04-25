#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
using ll = long long;
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline ll R(){
	ll ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

const int N = 1e5+1;

ll n, mn, l, r, sum, p, f;

int main(){
	while((n = R()) != 0){
		sum = 0;
		mn = 1e12 + 1;
		FOR(i,n){
			p = R(), f = R();
			if(i == 0) l = p;
			if(i == n-1) r = p;
			mn = mn > f ? f : mn;
			sum += f;
		}
		printf("%lld\n", sum < r-l ? mn : (sum - r + l) / n);
	}
}