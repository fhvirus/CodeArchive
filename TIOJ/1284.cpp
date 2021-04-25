// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
#define FOR(i,n) for(int i = 0; i < n; ++i)
const int N = 1e5 + 225;
int n;
double v[N], s[N];
inline double get(double p){
	double mx = 0, mn = 1e12, tmp;
	FOR(i,n){
		tmp = s[i] + v[i] * p;
		mx = (mx > tmp ? mx : tmp);
		mn = (mn < tmp ? mn : tmp);
	}
	return mx - mn;
}

int main(){
	n = R();
	FOR(i,n) v[i] = R(), s[i] = R();
	double l = 0, r = 1000000, m1, m2, a1, a2;
	const double eps = 1e-8;
	while(r - l > eps){
		m1 = (l * 2 + r) / 3;
		m2 = (l + r * 2) / 3;
		a1 = get(m1);
		a2 = get(m2);
		if(a1 > a2) l = m1;
		else r = m2;
	}
	printf("%.2lf", get(l));
	return 0;
}