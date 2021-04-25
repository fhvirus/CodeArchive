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
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#include<bitset>
const int N = 100001;
std::bitset<N> dp;

int t, n, h;

int main(){
	t = R();
	for(; t; --t){
		n = R(); h = R();
		dp.reset(); dp[0] = 1;
		for(int x, y, z; n; --n){
			x = R(), y = R(), z = R();
			dp = dp << x | dp << y | dp << z;
		}
		int ans = 0;
		for(int i = h; i >= 0; --i) if(dp[i]){ ans = i; break;}
		if(ans > 0)printf("%d\n", ans);
		else puts("no solution");
	}
}