// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
#include<vector>
using namespace std;
typedef long long ll;
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}

void solve(int T, int n){
	vector<int> f(n + 1), d(n + 1), t(n + 1);
	for(int i = 1; i <= n; ++i) f[i] = R();
	for(int i = 1; i <= n; ++i) d[i] = R();
	for(int i = 1; i <= n; ++i) t[i] = R();
	ll ans = 0;
	vector<int> cur;
	for(int i = 1; i <= n; ++i){
		T -= t[i];
		if(T <= 0) break;

		ll sum = 0;
		vector<int> nv(T);
		int j = 0, k = 0, v = f[i];
		while(j + k < T){
			if(j == cur.size()) break;
			if(v <= 0) break;
			if(cur[j] >= v){
				nv[j + k] = cur[j];
				sum += cur[j];
				++j;
			} else {
				nv[j + k] = v;
				sum += v;
				v -= d[i];
				++k;
			}
		}
		while(j + k < T and j < cur.size()){
			nv[j + k] = cur[j];
			sum += cur[j];
			++j;
		}
		while(j + k < T and v > 0){
			nv[j + k] = v;
			sum += v;
			v -= d[i];
			++k;
		}

		nv.resize(j + k);

		nv.swap(cur);
		chmax(ans, sum);
	}
	printf("%lld\n", ans);
}

int main(){
	int T, n;
	while(T = R(), n = R()) solve(T, n);
	return 0;
}