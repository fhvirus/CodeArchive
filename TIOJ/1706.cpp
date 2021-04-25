#pragma Ofast
#pragma loop-opt(on)
#pragma GCC target("avx,avx2")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'-');if(c=='-'){a=0;while((c=RC())>='0')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n<0)OB[OP++]='-',n=-n;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int N = 1e5 + 1;
int n, m, a, b, d;
struct edge{
	int v, c, p;
	bool operator<(const edge &rhs) const{
		return c > rhs.c;
	}
};
int head[N], prv[N*2];
edge to[N*2];

// dijkstra
#define INF 2147483647
inline int dijkstra(int a, int b){
	vector<int> mind(n + 1, INF);
	priority_queue<edge> pq;
	mind[a] = 0;
	pq.push({a, 0, 0});
	while(!pq.empty()){
		edge e = pq.top(); pq.pop();
		if(e.c > mind[e.v]) continue;
		if(e.v == b) return e.c;
		for(int ptr = head[e.v]; ptr != -1; ptr = prv[ptr]){
			edge f = to[ptr];
			int ndist = f.c + mind[e.v];
			if(ndist < mind[f.v])
				mind[f.v] = ndist, pq.push({f.v, ndist, 0});
		}
	}
	return INF;
}

int main(){
	n = R(), m = R(), a = R(), b = R(), d = R();
	for(int i = 1; i <= n; ++i)
		head[i] = -1;
	for(int i = 0, j = 0, u, v, c1, p1, c2, p2; i < m; ++i){
		u = R(), v = R(), c1 = R(), p1 = R(), c2 = R(), p2 = R();
		to[j] = {v, c1, p1}, prv[j] = head[u], head[u] = j++;
		to[j] = {u, c2, p2}, prv[j] = head[v], head[v] = j++;
	}

	int ans = dijkstra(a, b) + dijkstra(b, a);

	for(int i = 0; i < m * 2; ++i)
		to[i].c += to[i].p * (d - 1);

	W(min(ans, dijkstra(a, b) + dijkstra(b, a)));
	return 0;
}