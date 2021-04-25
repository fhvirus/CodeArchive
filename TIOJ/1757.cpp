#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline long long R(){
	long long ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}
#define M 1000000007
struct mat{
	long long a, b, c, d;
	mat operator*(const mat &rhs){
		return {
			(a * rhs.a + b * rhs.c) % M,  (a * rhs.b + b * rhs.d) % M,
			(c * rhs.a + d * rhs.c) % M,  (c * rhs.b + d * rhs.d) % M
		};
	}
};

mat pre[65];
inline void init(){
	pre[0] = {1, 1, 1, 0};
	for(int i = 1; i < 65; ++i)
		pre[i] = pre[i-1] * pre[i-1];
}
mat pow(long long e){
	mat ans = {1, 0, 0, 1};
	for(int i = 0; (1ll<<i) <= e; ++i){
		if(e&(1ll<<i)) ans = ans * pre[i];
	}
	return ans;
}

int t;
long long a, b, n;

int main(){
	init();
	t = R();
	for(; t; --t){
		a = R() % M, b = R() % M, n = R();
		n -= 2;
		mat jizz = pow(n);
		W((jizz.a * b + jizz.b * a) % M);
	}
	fwrite(outbuf, 1, outp, stdout);
	return 0;
}