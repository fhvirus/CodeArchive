#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
inline double RB(){
	double ans = 0, times = .1;
	char c = readchar();
	while(c<'0') c = readchar();
	while(c>='0' and c!='.') ans = ans * 10 + (double)(c ^ '0'), c = readchar();
	c = readchar();
	while(c>='0') ans += times * (c-'0'), times*=.1, c=readchar();
	return ans;
}
#include<vector>
#include<cmath>
#include<queue>
using namespace std;

const int N = 1e4 + 1, INF = 8e7;
int n, m, s, t;
struct edge{
	int v;
	double c;
	bool operator<(const edge &rhs) const{
		return c > rhs.c;
	}
};
vector<edge> adj[N];

// Dijkstra
double mind[N];
priority_queue<edge> pq;

int main(){
	n = R(), m = R(), s = R(), t = R();
	int a, b; double c;
	for(; m; --m){
		a = R(), b = R(), c = RB();
		adj[a].push_back({b, log10(c + 1)});
	}
	for(int i = 1; i <= n; ++i) mind[i] = INF;
	mind[s] = 0;
	pq.push({s, 0});
	while(!pq.empty()){
		edge e = pq.top(); pq.pop();
		if(e.c != mind[e.v]) continue;
		if(e.v == t){
			printf("%.2lfe+%03d", pow(10, (e.c - floor(e.c))), (int)floor(e.c));
			return 0;
		}
		for(edge f: adj[e.v]){
			double ndist = f.c + mind[e.v];
			if(ndist < mind[f.v])
				mind[f.v] = ndist, pq.push({f.v, ndist});
		}
	}
}