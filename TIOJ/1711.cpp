// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<vector>
#include<algorithm>
using namespace std;
typedef vector<int> vint;
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}

const int N = 1001;
int n, k, t[N];
vint adj[N];

int sz[N];
pair<vint, vint> dps(int u, int p){
	sz[u] = 1;
	vint dp0(1, t[u]), dp1(1, t[u]);

	for(int v: adj[u]){
		if(v == p) continue;
		auto [sc0, sc1] = dps(v, u);

		int tps = min(k, (sz[v] + sz[u]) * 2 - 2) + 1;
		vint tp0(tps, 0), tp1(tps, 0);

		// only old
		for(int i = 0, b = min(k, sz[u] * 2 - 2); i <= b; ++i){
			chmax(tp0[i], dp0[i]);
			chmax(tp1[i], dp1[i]);
		}
		// old & new
		for(int i = 0, b = min(k, sz[u] * 2 - 2); i <= b; ++i){
			for(int j = 0, c = min(k, sz[v] * 2 - 2); j <= c; ++j){
				if(i + j + 1 > k) break;
				chmax(tp1[i + j + 1], dp0[i] + sc1[j]);
				if(i + j + 2 > k) continue;
				chmax(tp0[i + j + 2], dp0[i] + sc0[j]);
				chmax(tp1[i + j + 2], dp1[i] + sc0[j]);
			}
		}
		tp0.swap(dp0);
		tp1.swap(dp1);
		sz[u] += sz[v];
	}

	return {dp0, dp1};
}

int main(){
	n = R(), k = R();
	for(int i = 1; i <= n; ++i) t[i] = R();
	for(int i = 1, u, v; i < n; ++i){
		u = R(), v = R();
		adj[u].pb(v);
		adj[v].pb(u);
	}
	auto [dp0, dp1] = dps(1, 0);
	W(*max_element(AI(dp1)));
	return 0;
}