// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<string>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;}

void RS(string &s){
	s = "";
	char c;
	while(true){
		c = RC();
		if('a' <= c and c <= 'z') s.push_back(c);
		else break;
	}
}

const int INF = 1e9;
const int N = 2e5 + 225, M = 1e9 + 7;
int t, n, a[N];

struct AhoCorasick{
	static const int C = 2001, S = 3;
	short ch[C][S], fa[C], pt = 0;
	int sc[C];
	inline int eek(char c){ return c == 'r' ? 0 : (c == 'g' ? 1 : 2);}
	inline void ins(string s, int v){
		int u = 0;
		for(auto c: s){
			c = eek(c);
			if(!ch[u][c]) ch[u][c] = ++pt;
			u = ch[u][c];
		}
		sc[u] += v;
	}
	inline void build(){
		queue<int> q;
		FOR(i,S) if(ch[0][i]) q.push(ch[0][i]);
		while(!q.empty()){
			int u = q.front(); q.pop();
			sc[u] += sc[fa[u]];
			FOR(i,S){
				if(ch[u][i]){
					fa[ch[u][i]] = ch[fa[u]][i];
					q.push(ch[u][i]);
				}
				else
					ch[u][i] = ch[fa[u]][i];
			}
		}
	}
	int dps[2][C];
	inline int solve(string t){
		auto dp = dps[0], tm = dps[1];
		fill(dp, dp + pt + 1, -INF);
		dp[0] = 0;
		for(char c: t){
			fill(tm, tm + pt + 1, -INF);
			if(c == 'x'){
				FOR(i,S){
					FOO(u,0,pt){
						int v = ch[u][i];
						chmax(tm[v], dp[u] + sc[v]);
					}
				}
			} else {
				c = eek(c);
				FOO(u,0,pt){
					int v = ch[u][c];
					chmax(tm[v], dp[u] + sc[v]);
				}
			}
			swap(dp, tm);
		}
		return *max_element(dp, dp + pt + 1);
	}
} AC;
int32_t main(){
	int n, k; n = R(), k = R();
	FOR(i,k){
		string s; int v;
		RS(s); v = R();
		AC.ins(s, v);
	}
	AC.build();
	string t; RS(t);
	W(AC.solve(t));
	return 0;
}
