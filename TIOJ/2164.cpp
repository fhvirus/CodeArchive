#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar(); bool minus = false;
	while(c<'-') c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#define ll long long
#define N 5000
#define INF 1e18
int n;
struct point{
	ll x, y, z;
} p[N];
inline ll dist(point a, point b){
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}
bool vis[N];
ll ans, d[N];

inline ll min(ll a, ll b){
	return a < b ? a : b;
}

int main(){
	n = R();
	FOR(i, n) p[i] = {R(), R(), R()}, d[i] = INF;
	vis[0] = true;
	d[0] = 0;
	int cur = 0;
	for(int i = 1; i < n; ++i){
		int jizz = 0; ll mn = INF;
		for(int j = 0; j < n; ++j) if(!vis[j]){
			d[j] = min(d[j], dist(p[cur], p[j]));
			if(d[j] < mn) mn = d[j], jizz = j;
		}
		vis[jizz] = true;
		ans += mn;
		cur = jizz;
	}
	printf("%lld", ans);
}