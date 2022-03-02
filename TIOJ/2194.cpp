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
inline ll cdiv(ll x,ll m){return x/m+(x%m?(x<0)^(m>0):0);}
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}

const ll INF = 4e18;
vector<int> f, d, t;

ll check(int p, int lim){
	ll tot = 0;
	for(int i = 1; i <= p; ++i){
		if(d[i] == 0){
			if(f[i] >= lim) return INF;
			continue;
		}
		if(f[i] < lim) continue;
		tot += cdiv(f[i] - lim + 1, d[i]);
	}
	return tot;
}

ll calc(int T, int p){
	int l = 0, r = 1e9 + 1, m;
	while(l < r) {
		// choose every value >= l
		m = (l + r) / 2;
		ll ret = check(p, m);
		if(ret > T) l = m + 1;
		else r = m;
	}

	ll ans = 0;
	for(int i = 1; i <= p; ++i){
		if(f[i] < l) continue;
		ll x = cdiv(f[i] - l + 1, d[i]);
		ans += ((ll)f[i] + (f[i] - (ll)d[i] * (x-1))) * x / 2;
		T -= x;
	}

	if(l - 1 > 0) ans += 1ll * (l-1) * T;

	return ans;
}

void solve(int n, int T){
	f.assign(n + 1, 0);
	d.assign(n + 1, 0);
	t.assign(n + 1, 0);
	for(int i = 2; i <= n; ++i) t[i] = R();
	for(int i = 1; i <= n; ++i) f[i] = R();
	for(int i = 1; i <= n; ++i) d[i] = R();

	ll ans = 0;
	for(int i = 1; i <= n; ++i){
		T -= t[i];
		if(T <= 0) break;
		chmax(ans, calc(T, i));
	}
	printf("%lld\n", ans);
}

int main(){
	int n, m;
	n = R(), m = R();
	solve(n, m);
	return 0;
}
