// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n, char e){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}
inline void WL(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<algorithm>
#include<vector>
#include<queue>
#include<functional>
#include<utility>
using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;}
const ll INF = 4e18;
const int N = 1000002, M = 5000005;

int n, m;
pli dis[N];
int he[N], to[M], di[M], pr[M];
priority_queue<pli, vector<pli>, greater<pli>> pq;

int32_t main(){
	n = R(), m = R();
	for(int u = 1; u <= n + 1; ++u){
		he[u] = -1;
		dis[u] = {INF, 0};
	}
	for(int u, v, d, i = 0; i < m; ++i){
		u = R(), v = R(), d = R();
		if(u == v) continue;
		to[i] = v;
		di[i] = d;
		pr[i] = he[u];
		he[u] = i;
	}
	dis[1] = {0, 0};
	pq.emplace(0, 1);
	while(!pq.empty()){
		auto [d, u] = pq.top(); pq.pop();
		if(d > dis[u].ff) continue;
		if(u == n + 1) break;
		for(int e = he[u], v, d; e != -1; e = pr[e]){
			v = to[e]; d = di[e];
			if(chmin(dis[v], {dis[u].ff + d, u}))
				pq.emplace(dis[v].ff, v);
		}
	}

	vector<int> ans;
	int u = n + 1;
	while(u != 0){
		ans.pb(u);
		u = dis[u].ss;
	}
	reverse(AI(ans));

	WL(dis[n + 1].ff);
	for(int i = 0; i < ans.size(); ++i)
		W(ans[i], "-\n"[i == ans.size() - 1]);
	write(1,OB,OP);
	return 0;
}
