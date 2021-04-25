#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<unistd.h>
const int S = 1<<10;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0';
    if(n < 0) outbuf[outp++] = '-', n = -n;
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) write(1, outbuf, outp), outp = 0;
}

const int JIZZ = 3163;
int primes[1000], p;
bool notprime[JIZZ];

inline long long pow(long long a, long long e){
	long long ans = 1;
	while(e) (e&1) and (ans *= a), a *= a, e >>= 1;
	return ans;
}
int t, n;
int in[1000], owo[1000], ptr, cnt, sum;

signed main(){
	notprime[0] = notprime[1] = true;
	for(int i = 2; i < JIZZ; ++i){
		if(!notprime[i]) primes[p++] = i;
		for(int j = 0; j < p; ++j){
			if(i * primes[j] > JIZZ) break;
			notprime[i * primes[j]] = true;
			if(i % primes[j] == 0) break;
		}
	}

	t = R();
	for(; t; --t){
		n = R(), ptr = 0;
		for(int i = 0; primes[i] * primes[i] <= n and i < p; ++i){
			if(n % primes[i] == 0){
				owo[ptr] = 0;
				in[ptr] = primes[i];
				while(n > 0 and n % primes[i] == 0)
					n /= primes[i], ++owo[ptr];
				++ptr;
			}
		}
		if(n > 1) in[ptr] = n, owo[ptr] = 1, ++ptr;
		cnt = sum = 1;
		for(int i = 0; i < ptr; ++i)
			cnt *= owo[i] + 1,
			sum *= (pow(in[i], owo[i] + 1) - 1) / (in[i] - 1);
		W(cnt * sum);
	}
	write(1, outbuf, outp);
}