#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'-');if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
using namespace std;

const int N = 5000;
int n, m, a[N], q[N];
struct eek{ int q; short d, x;} p[N];
long long dp[N];
int app[10001];
int main(){
	n = R(), m = R();
	for(int i = 1; i <= m; ++i) a[i] = R();
	for(int i = 0; i < n; ++i)
		p[i] = {R(), (short)R(), (short)R()}, app[p[i].x]++;

	bool hulan = true;
	for(int i = 1; i < 10001; ++i)
		if(app[i] > 1){ hulan = false; break;}
	if(hulan){
		long long ans = 0;
		for(int i = 0; i < n; ++i)
			if(p[i].q > 0) ans += p[i].q;
		W(ans);
		return 0;
	}

	sort(p, p + n, [](eek a, eek b){
		return a.d < b.d;
	});
	for(int i = 0; i < n; ++i){
		long long cur = 0;
		for(int j = 0; j < i; ++j){
			if(p[i].x == 0 or p[i].x != p[j].x)
				cur = max(cur, dp[j]);
			else
				cur = max(cur, dp[j] - a[p[j].x]);
		}
		dp[i] = cur + p[i].q;
	}

	long long ans = 0;
	for(int i = 0; i < n; ++i)
		ans = max(ans, dp[i]);
	W(ans);
	return 0;
}