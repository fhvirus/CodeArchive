#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<unistd.h>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p == q and (q = (p = buf) + read(0, buf, S)) == buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c < '0') c = readchar();
	while(c >= '0') ans = ans * 10 + (c ^ '0'), c = readchar();
	return ans;
}

const int N = 11294000;
bool notprime[N];
int primes[745001], ppp, emirps[100075], eee;
inline bool isprime(int eek){
	if(eek < N) return !notprime[eek];
	for(int i = 0; i < ppp; ++i){
		if(primes[i] * primes[i] > eek) break;
		if(eek % primes[i] == 0) return false;
	}
	return true;
}
inline bool jizz(int p){
	int owo = p, eek = 0;
	while(p > 0) eek = eek * 10 + p % 10, p /= 10;
	if(eek == owo) return false;
	return isprime(eek);
}
inline void shai(){
	notprime[0] = notprime[1] = true;
	for(int i = 2; i < N; ++i){
		if(!notprime[i]) primes[ppp++] = i;
		for(int p = 0; p < ppp; ++p){
			if(i * primes[p] > N) break;
			notprime[i * primes[p]] = true;
			if(i % primes[p] == 0) break;
		}
	}
	for(int p = 0; p < ppp; ++p)
		if(jizz(primes[p]))
			emirps[eee++] = primes[p];
}
#include<cstdio>
int t;
int main(){
	shai();
	t = R();
	for(; t; --t) printf("%d\n", emirps[R()-1]);
}