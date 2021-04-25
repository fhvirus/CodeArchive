// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
const int N = 2e5 + 225;
typedef long long ll;
int n, L;
ll a[N], b[N];
#define min(a,b) (a<b?a:b)
inline bool check(ll d){
	ll p = 0, cur;
	for(int i = L; i <= n; ++i){
		p = min(p, a[i - L] - d * b[i - L]);
		cur = a[i] - d * b[i];
		if(cur >= p) return true;
	}
	return false;
}
inline bool check(double d){
	double p = 0, cur;
	for(int i = L; i <= n; ++i){
		p = min(p, a[i - L] - d * b[i - L]);
		cur = a[i] - d * b[i];
		if(cur >= p) return true;
	}
	return false;
}
int main(){
	n = R(), L = R();
	for(int i = 1; i <= n; ++i) a[i] = a[i-1] + R();
	for(int i = 1; i <= n; ++i) b[i] += b[i-1] + R();

	ll u = 0, v = 100225, w;
	while(v - u > 1){
		w = (u + v) / 2;
		if(check(w)) u = w;
		else v = w;
	}

	double l = u, r = v, m;
	const double eps = 1e-5;
	while(r - l > eps){
		m = (l + r) / 2;
		if(check(m)) l = m;
		else r = m;
	}
	printf("%.5lf", l);
	return 0;
}
