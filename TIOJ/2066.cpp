#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<17;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

#include<algorithm>
using namespace std;
#define N 100000
#define M 2305843009213693951ll
int t, n, k, a[N];
int des[N], e;
long long ans;

long long val[N+1];
void init(){
	fill(val, val + e, 0ll);
}
void modify(int p, long long v){
	for(; p <= e; p += p & -p) val[p] = (val[p] + v) % M;
}
long long query(int p){
	long long ans = 0;
	for(; p; p ^= p & -p) ans = (ans + val[p]) % M;
	return ans;
}
long long dp[N];

int main(){
	t = R();
	for(; t; --t){
		n = R(), k = R(); ans = n;
		int mx = 0;
		FOR(i, n) des[i] = a[i] = R(), dp[i] = 1;
		sort(des, des + n);
		e = unique(des, des + n) - des;
		FOR(i, n) a[i] = lower_bound(des, des + e, a[i]) - des + 1;
		for(int l = 2; l <= k; ++l){
			init();
			FOR(i, n){
				long long v = query(a[i]-1);
				ans = (ans + v) % M;
				modify(a[i], dp[i]);
				dp[i] = v;
			}
		}
		printf("%lld\n", ans);
	}
}