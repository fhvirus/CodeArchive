// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii;
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
const ll INF = 4e18;
const int N = 1e5 + 225;

template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;

int he[N], to[N], we[N], pr[N];

void solve(){
	int n, m; n = R(), m = R();
	int a, b; a = R(), b = R();
	FOR(i,n) he[i] = -1;
	FOR(e,m){
		int u, v, c;
		u = R(), v = R(), c = R();
		to[e] = v; we[e] = c; pr[e] = he[u]; he[u] = e;
	}
	vector<ll> dis(n, INF), did(n, INF);
	minheap<pair<ll, int>> pq;
	dis[a] = 0; pq.emplace(dis[a], a);
	while(!pq.empty()){
		auto [d, u] = pq.top(); pq.pop();
		if(did[u] < d) continue;
		for(int e = he[u]; e != -1; e = pr[e]){
			int v = to[e], c = we[e];
			ll nd = d + c;
			if(nd < dis[v]){
				swap(dis[v], nd);
				pq.emplace(dis[v], v);
			}
			if(nd < did[v] && nd != dis[v]){
				swap(did[v], nd);
				pq.emplace(did[v], v);
			}
		}
	}
	W(did[b] - dis[b]);
}

int main(){
	for(int t = R(); t; --t) solve();
	write(1,OB,OP);
	return 0;
}
