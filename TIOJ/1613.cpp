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

typedef long long ll;
const int N = 1e6;
#include<queue>
#include<functional>
using namespace std;
priority_queue<ll, vector<ll>, greater<ll>> pq;

int n;
long long ans;
int main(){
	n = R();
	for(; n; --n) pq.push(R());
	while(pq.size() > 1){
		ll a = pq.top(); pq.pop();
		ll b = pq.top(); pq.pop();
		ans += a + b;
		pq.push(a + b);
	}
	printf("%lld\n", ans);
}