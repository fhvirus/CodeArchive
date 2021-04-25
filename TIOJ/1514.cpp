#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

const int N = 1000010;
int n, primes[N+1], p, phi[N+1];
long long ans[N+1];

int main(){
	ans[1] = 3;
	for(long long i = 2; i <= N; ++i){
		if(phi[i] == 0) phi[i] = i-1, primes[p++] = i;
		for(int j = 0; j < p; ++j){
			if(i * primes[j] > N) break;
			if(i % primes[j] == 0){
				phi[i * primes[j]] = phi[i] * primes[j];
				break;
			}
			phi[i * primes[j]] = phi[primes[j]] * phi[i];
		}
	}
	for(int i = 2; i <= N; ++i) ans[i] = ans[i-1] + phi[i] * 2;
	while((n = R()) > 0) printf("%lld\n", ans[n]);
}