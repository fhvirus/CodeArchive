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

#include<vector>
#include<algorithm>
using namespace std;
const int N = 1e5, M = 1e9 + 7;
int t, n, m, sz[N], a[N], b[N], eek;
long long ans, cross[N], primes[N];
vector<int> adj[N];

int dfs(int u, int p){
	sz[u] = 1;
	for(int v: adj[u])
		if(v != p){
			sz[u] += dfs(v, u);
		}
	return sz[u];
}

int main(){
	t = R();
	for(; t; --t){
		n = R(); ans = 0;
		for(int i = 1; i <= n; ++i) adj[i].clear(), sz[i] = 0;
		FOR(i, n-1){
			a[i] = R(), b[i] = R();
			adj[a[i]].push_back(b[i]);
			adj[b[i]].push_back(a[i]);
		}
		dfs(1, 0);
		FOR(i, n-1){
			eek = min(sz[a[i]], sz[b[i]]);
			cross[i] = (long long)eek * (long long)(sz[1] - eek);
		}
		sort(cross, cross + n - 1);
		FOR(i, n-1) cross[i] %= M;

		m = R();
		FOR(i, m) primes[i] = R();
		while(m < n-1) primes[m++] = 1;
		sort(primes, primes + m);
		while(m > n-1) primes[m-2] = primes[m-1] * primes[m-2] % M, --m;

		FOR(i, n-1){
			ans = (ans + cross[i] * primes[i] % M) % M;
		}
		printf("%lld\n", ans);
	}
}