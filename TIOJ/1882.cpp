#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}


#include<cstdio>
inline long long min(long long a, long long b){ return a < b ? a : b;}
inline double min(double a, double b){ return a < b ? a : b;}

const int N = 10000;
int n;
int a[N], b[N], c[N];

inline long long geti(long long x){
	long long minY = a[0] * x * x + b[0] * x + c[0];
	for(int j = 1; j < n; ++j)
		minY = min(minY, a[j] * x * x + b[j] * x + c[j]);
	return minY;
}

inline double get(double x){
	double minY = a[0] * x * x + b[0] * x + c[0];
	for(int j = 1; j < n; ++j)
		minY = min(minY, a[j] * x * x + b[j] * x + c[j]);
	return minY;
}

int main(){
	n = R();
	for(int i = 0; i < n; ++i)
		a[i] = R(), b[i] = R(), c[i] = R();

	//Ternary Search
	int li, m1i, m2i, ri;
	li = 0, ri = 130000;
	while(li < ri - 2){
		m1i = (li * 2 + ri) / 3;
		m2i = (li + ri * 2) / 3;
		(geti(m1i) < geti(m2i)) ? li = m1i : ri = m2i;
	}

	double l, m1, m2, r;
	const double prec = 1e-7;
	l = li, r = ri;
	while(r - l > prec){
		m1 = (l*2 + r)/3;
		m2 = (l + r*2)/3;
		(get(m1) < get(m2)) ? l = m1 : r = m2;
	}
	printf("%.6lf\n", (l + r) / 2);
	return 0;
}