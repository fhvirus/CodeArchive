#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
#include<vector>
#include<algorithm>
#include<unordered_set>
using namespace std;

const int N = 2e5+1, M = 5e5;
int n, m, k;
int head[N], from[M<<1], to[M<<1], prv[M<<1];
// BCC
int low[N], pre[N], t;
int bcc[N], bcnt, cnt[N];
int stk[N], top;
void bccdfs(int u, int p){
	low[u] = pre[u] = ++t;
	stk[top++] = u;
	for(int e = head[u], v; e != -1; e = prv[e]){
		v = to[e];
		if(pre[v] == 0)
			bccdfs(v, u), low[u] = min(low[u], low[v]);
		else if(pre[v] < pre[u] and v != p)
			low[u] = min(low[u], pre[v]);
	}
	if(low[u] == pre[u]){
		++bcnt;
		int v;
		do bcc[v = stk[--top]] = bcnt, ++cnt[bcnt]; while(v != u);
	}
}

// centree
long long ans;
vector<int> adj[N];
bool vis[N];
int sz[N];
int getSize(int u, int p){
	int s = 1;
	for(int v: adj[u])
		if(!vis[v] and v != p)
			s += getSize(v, u);
	return sz[u] = s;
}
int getCentroid(int u, int p, int s){
	for(int v: adj[u])
		if(v != p and !vis[v] and (sz[v]<<1) > s)
			return getCentroid(v, u, s);
	return u;
}
void dfs(int u, int p, int d, vector<int> &dis){
	if(d > k) return;
	dis[d] += cnt[u];
	for(int v: adj[u])
		if(v != p and !vis[v]) dfs(v, u, d + 1, dis);
}
int centroidDecomp(int u, int p){
	getSize(u, p);
	int c = getCentroid(u, p, sz[u]);
	vis[c] = true;
	// solve with root = c
	vector<int> alldis(k + 1, 0);
	alldis[0] = cnt[c];
	for(int v: adj[c]){
		if(vis[v]) continue;
		vector<int> subdis(k + 1, 0);
		dfs(v, c, 1, subdis);
		for(int i = 0; i <= k; ++i)
			ans += 2 * alldis[i] * subdis[k - i];
		for(int i = 0; i <= k; ++i)
			alldis[i] += subdis[i];
	}

	// recursive solve
	for(int v: adj[c])
		if(!vis[v])
			centroidDecomp(v, c);
	return c;
}

int main(){
	n = R(), m = R(), k = R();
	for(int i = 0; i <= n; ++i) head[i] = -1;

	unordered_set<int> sss;
	for(int a, b, i = 0, j = 0; i < m; ++i){
		a = R(), b = R();
		if(a == b) continue;
		if(a > b) swap(a, b);
		if(sss.count(a * 1000000ll + b)) continue;
		sss.insert(a * 1000000ll + b);
		from[j] = a, to[j] = b, prv[j] = head[a], head[a] = j++;
		from[j] = b, to[j] = a, prv[j] = head[b], head[b] = j++;
	}

	// find bcc
	for(int i = 1; i <= n; ++i)
		if(bcc[i] == 0) bccdfs(i, 0);

	// bcc -> tree
	for(int i = 0; i < m<<1; i += 2)
		if(bcc[from[i]] != bcc[to[i]])
			adj[bcc[from[i]]].push_back(bcc[to[i]]),
			adj[bcc[to[i]]].push_back(bcc[from[i]]);

	// centroid decomp.
	for(int i = 1; i <= bcnt; ++i)
		if(!vis[i]) centroidDecomp(i, 0);

	printf("%lld", ans);
}