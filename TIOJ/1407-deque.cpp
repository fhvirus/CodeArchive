//Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<utility>
using namespace std;
#define pii pair<int, int>
#define ff first
#define ss second
#define FOR(i,n) for(int i = 0; i < n; ++i)
inline void tmx(int &a, int b){ (a < b) && (a = b);}

const int N = 1e5 + 225, INF = 8e7 * 25, M = 1e6 + 225;
int n, w[N], m[N], c[N], T;
int dp[M];
struct{
	pii val[M];
	int h = 0, t = 0;
	inline void clear(){ h = t = 0;}
	inline void push_back(pii p){ val[t++] = p;}
	inline void pop_front(){ ++h;}
	inline void pop_back(){ --t;}
	inline bool empty(){ return h == t;}
	inline pii  front(){ return val[h];}
	inline pii  back(){ return val[t-1];}
} dq;

int main(){
	n = R();
	FOR(i,n) w[i] = R(), m[i] = R(), c[i] = R();
	T = R();
	FOR(i,n){
		int ww = w[i], mm = m[i], cc = c[i];
		for(int st = 0; st < ww; ++st){
			dq.clear();
			dq.push_back({0, dp[st]});
			for(int j = 1; st + j * ww <= T; ++j){
				while(!dq.empty() and dq.front().ff < j - cc) dq.pop_front();
				int eek = dq.front().ss + mm * (j - dq.front().ff);
				while(!dq.empty() and dq.back().ss + mm * (j - dq.back().ff) <= dp[st + j * ww])
					dq.pop_back();
				dq.push_back({j, dp[st + j * ww]});
				tmx(dp[st + j * ww], eek);
			}
		}
	}
	int ans = 0;
	FOR(i,T+1) tmx(ans, dp[i]);
	W(ans);
	return 0;
}
