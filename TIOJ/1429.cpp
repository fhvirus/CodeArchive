#pragma GCC optimize("Ofast")
#define ll long long
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(ll n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}
inline ll max(ll a, ll b){ return a > b ? a : b;}
#include<queue>
using namespace std;

#define mxpq priority_queue<int>
const int N = 1e5 + 1;
int n, m, b[N], c[N], l[N], sz[N];
int head[N], to[N*2], prv[N*2];

ll ans = 0;

int getSize(int u, int p){
	sz[u] = 1;
	for(int v = head[u]; v != -1; v = prv[v])
		if(to[v] != p)
			sz[u] += getSize(to[v], u);
	return sz[u];
}

int dfs(int u, int p, mxpq &pq){
	ll heapsum = 0;
	int mxc = -1, mxcsz = 0;
	for(int v = head[u]; v != -1; v = prv[v])
		if(to[v] != p and mxcsz < sz[to[v]])
			mxc = to[v], mxcsz = sz[to[v]];

	if(mxc != -1) heapsum = dfs(mxc, u, pq);

	mxpq tmp;
	for(int v = head[u]; v != -1; v = prv[v]){
		if(to[v] == mxc or to[v] == p) continue;
		heapsum += dfs(to[v], u, tmp);
		while(!tmp.empty())
			pq.push(tmp.top()), tmp.pop();
	}

	pq.push(c[u]);
	heapsum += c[u];
	while(!pq.empty() and heapsum > m){
		heapsum -= pq.top();
		pq.pop();
	}
	ans = max(ans, (ll)l[u] * (ll)pq.size());

	return heapsum;
}

int main(){
	n = R(), m = R();
	for(int i = 1; i <= n; ++i)
		head[i] = -1;
	for(int i = 1, j = 0; i <= n; ++i){
		b[i] = R(), c[i] = R(), l[i] = R();
		to[j] = b[i], prv[j] = head[i], head[i] = j++;
		to[j] = i, prv[j] = head[b[i]], head[b[i]] = j++;
	}
	getSize(1, 0);

	mxpq jizz;
	dfs(1, 0, jizz);
	W(ans);
	return 0;
}