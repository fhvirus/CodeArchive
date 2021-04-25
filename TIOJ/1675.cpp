// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<vector>
#include<algorithm>
#include<tuple>
using namespace std;
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}

int main(){
	int n, c, p; n = R(), c = R(), p = R();
	vector<int> dp(p + 1, 0); dp[p] = c;
	vector<tuple<int, int, int>> tsk;
	for(int ci, ai, pi; n; --n){
		ci = R(), ai = R(), pi = R();
		if(ai <= ci) continue;
		if(pi > p) continue;
		tsk.pb(ci, ai, pi);
	}
	sort(AI(tsk));
	for(auto [ci, ai, pi]: tsk){
		for(int i = 0; i + pi <= p; ++i){
			if(dp[i + pi] < ci) continue;
			chmax(dp[i], dp[i + pi] - ci + ai);
		}
	}
	int mx = 0;
	for(int i = 1; i <= p; ++i) chmax(mx, dp[i]);
	W(mx);
	return 0;
}
