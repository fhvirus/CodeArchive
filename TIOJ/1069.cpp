#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<algorithm>
#include<vector>
using namespace std;

#define MAXN 2001

struct vertex{
	int x, y, t;
} v[1001];
inline int dist(vertex a, vertex b){
	return abs(a.x - b.x) + abs(a.y - b.y);
}

vector<short> adj[1001];
int match[MAXN], t, vis[MAXN];

inline int greedy_matching(int n){
	int ans = 0;
	for(int i = 1; i <= n; ++i)
		if(match[i] == 0)
			for(int j: adj[i])
				if(match[j] == 0){
					match[i] = j;
					match[j] = i;
					++ans;
					break;
				}
	return ans;
}

bool dfs(int u){
	if(vis[u] == t) return false;
	vis[u] = t;
	for(short v: adj[u])
		if(!match[v] or dfs(match[v])){
			match[v] = u;
			match[u] = v;
			return true;
		}
	return false;
}
inline int get_max_matching(int n){
	int ans = greedy_matching(n);
	for(int i = 1; i <= n; ++i)
		if(match[i] == 0)
			t++, ans += dfs(i);
	return ans;
}

int main(){
	int T, n;
	T = R();
	for(;T;--T){
		n = R();
		for(int i = 1; i <= n; ++i){
			v[i].t = R(); v[i].x = R(); v[i].y = R();
			adj[i].clear();
			match[i] = vis[i] = 0;
			match[i+n] = vis[i+n] = 0;
		}
		sort(v+1, v + n+1, [](vertex a, vertex b){
			return a.t < b.t;
		});
		for(int i = 1; i <= n; ++i)
			for(int j = i+1; j <= n; ++j)
				if(i != j and v[j].t - v[i].t >= dist(v[i], v[j]))
					adj[i].push_back(j+n);

		W(n - get_max_matching(n));
	}
	write(1,OB,OP);
	return 0;
}