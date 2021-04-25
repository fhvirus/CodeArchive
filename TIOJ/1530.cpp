#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=ans*10+(c^'0'), c=readchar();
	return ans;
}
#include<algorithm>
using namespace std;

#define ll long long
const int N = 5e5+1;
const ll INF = 1e18;
int n, m, s, e;
ll d[N], tmp[N];
struct edge{
	int u, v, t, p;
	bool operator<(const edge &rhs) const{
		return p < rhs.p;
	}
} E[N];

int main(){
	n = R(), m = R(), s = R(), e = R();
	for(int i = 0; i < m; ++i)
		E[i] = {R(), R(), R(), R()};
	
	sort(E, E + m);
	fill(d, d + m + 1, INF);
	d[s] = 0;

	for(int i = 0; i < m; ++i){
		int l = i;
		for(; i < m and E[i].p == E[l].p; ++i)
			tmp[E[i].u] = tmp[E[i].v] = INF;
		for(int j = l; j < i; ++j){
			tmp[E[j].v] = min(tmp[E[j].v], min(d[E[j].v], d[E[j].u] + E[j].t));
			tmp[E[j].u] = min(tmp[E[j].u], min(d[E[j].u], d[E[j].v] + E[j].t));
		}
		for(int j = l; j < i; ++j){
			d[E[j].u] = min(d[E[j].u], tmp[E[j].u]);
			d[E[j].v] = min(d[E[j].v], tmp[E[j].v]);
		}
		--i;
	}
	if(d[e] == INF) puts("Pipi how way!!!");
	else printf("%lld", d[e]);
}