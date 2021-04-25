#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
inline int gcd(int a, int b){
	while(b){
		a %= b;
		a^=b^=a^=b;
	}
	return a;
}

const int N = 50;
int n, a[N], ans;
double pi;

#include<cmath>

int main(){
	while(n = R()){
		FOR(i,n) a[i] = R();
		ans = 0;
		for(int i = 1; i < n; ++i){
			for(int j = 0; j < i; ++j){
				if(gcd(a[i], a[j]) == 1)
					ans++;
			}
		}
		if(ans == 0) puts("No estimate for this data set.");
		else{
			pi = 1 / ((ans + .0)/(n * (n-1) / 2) / 6);
			printf("%.6lf\n", sqrt(pi));
		}
	}
	return 0;
}