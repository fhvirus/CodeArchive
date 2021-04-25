#pragma Ofast
#pragma loop-opt(on)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<vector>
#include<queue>
#include<functional>
#include<utility>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, ll> pil;
const int N = 1e5 + 225;
int n, l, c;
ll dp[N];
struct seg{
	int l, r, v;
} s[N];
int main(){
	for(int T = R(); T; --T){
		n = R(), l = R(), c = R();
		for(int i = 0, t; i < n; ++i){
			s[i].l = R(), t = R();
			s[i].r = s[i].l + t;
			s[i].v = c - (s[i].r);
		}
		sort(s, s + n, [](seg a, seg b){
			return a.l < b.l;
		});

		fill(dp, dp + n + 1, 0);
		priority_queue<pil, vector<pil>, greater<pil>> pq;
		ll curmax = 0;

		for(int i = 0; i < n; ++i){
			while(!pq.empty() and pq.top().first <= s[i].l){
				curmax = max(curmax, pq.top().second), pq.pop();
			}
			dp[i] = curmax + s[i].v;
			pq.push({s[i].r, dp[i]});
		}
		while(!pq.empty()) curmax = max(curmax, pq.top().second), pq.pop();
		W(curmax);
	}
	write(1,OB,OP);
	return 0;
}