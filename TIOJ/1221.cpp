#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#pragma GCC target("avx2")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
#include<queue>
#include<utility>
using namespace std;

const int N = 1e5 + 10, M = 5e5 + 10, INF = 8e7;
int n, k, p, ans, emp;
int a[M], last[N], head[N], nxt[M];
bool in[N];
priority_queue<pair<int, int>> pq;

int main(){
	n = R(), emp = k = R(), p = R();
	if(k >= n){ printf("%d", n); return 0;}
	FOR(i, p){
		a[i] = R();
		(last[a[i]] == 0 ? head[a[i]] : nxt[last[a[i]]]) = i;
		last[a[i]] = i;
	}
	FOR(i, p) if(nxt[i] == 0) nxt[i] = INF;

	FOR(i, p){
		head[a[i]] = nxt[head[a[i]]];
		if(!in[a[i]]){
			++ans;
			if(emp > 0) --emp;
			else in[pq.top().second] = false, pq.pop();
		}
		in[a[i]] = true, pq.push({head[a[i]], a[i]});
	}
	printf("%d\n", ans);
	return 0;
}