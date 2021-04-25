#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<vector>
#include<algorithm>
#include<numeric>
#include<utility>
using namespace std;

const int N = 325;

int n, m;
#define pii pair<int, int>
#define pipi pair<int, pii>
#define ff first
#define ss second
inline int dist(pii a, pii b){
	return max(abs(a.ff - b.ff), abs(a.ss - b.ss));
}
pipi ramen[N];
pii com[N];
int cntramen, cntcom, id[N];

int head[N], prv[N*N], to[N*N], e;
int match[N*2], vis[N], vt = 0;
bool dfs(int u){
	if(vis[u] == vt) return false;
	vis[u] = vt;
	for(int v = head[u]; v != -1; v = prv[v])
		if(!match[to[v]] or dfs(match[to[v]])){
			match[u] = to[v];
			match[to[v]] = u;
			return true;
		}
	return false;
}

int main(){
	n = R(), m = R();
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			int w = R();
			if(w > 0) ramen[cntramen++] = {w, {i, j}};
			if(w == 0) com[cntcom++] = {i, j};
		}
	}

	for(int i = 0; i <= cntcom; ++i)
		head[i] = -1;

	iota(id, id + cntramen, 0);
	for(int i = 0; i < cntcom; ++i){
		sort(id, id + cntramen, [&](int a, int b){
			return dist(com[i], ramen[a].ss) != dist(com[i], ramen[b].ss) ?
				dist(com[i], ramen[a].ss) < dist(com[i], ramen[b].ss) :
				ramen[a].ff > ramen[b].ff;
		});
		int mx = ramen[id[0]].ff;
		to[e] = id[0] + N, prv[e] = head[i + 1], head[i + 1] = e++;
		for(int j = 1; j < cntramen; ++j){
			if(ramen[id[j]].ff > mx)
				to[e] = id[j] + N, prv[e] = head[i + 1], head[i + 1] = e++;
			mx = max(mx, ramen[id[j]].ff);
		}
	}

	int ans = 0;
	for(int i = 1; i <= cntcom; ++i)
		if(!match[i]) ++vt, ans += dfs(i);
	W(ans);
	return 0;
}