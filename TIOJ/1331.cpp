#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<unistd.h>
#define int unsigned
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'-') c=readchar();
	if(c=='-') return 2e9;
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20], eekp;
int outp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) write(1, outbuf, outp), outp = 0;
}
struct mat{
	int a, b, c, d;
	mat operator*(const mat &eek){
		return {
			a * eek.a + b * eek.c, a * eek.b + b * eek.d,
			c * eek.a + d * eek.c, c * eek.b + d * eek.d
		};
	}
};
inline mat pow(mat a, int e){
	mat ans = {1, 0, 0, 1};
	while(e){
		if(e&1) (ans = ans * a);
		a = a * a, e >>= 1;
	}
	return ans;
}

int n, a, b, x, y;
signed main(){
	while(true){
		n = R();
		if(n == 2e9) break;
		a = R(), b = R(), x = R(), y = R();
		if(n == 0){ W(a); continue;}
		if(n == 1){ W(b); continue;}
		mat jizz = pow({y, x, 1, 0}, n-1);
		W(jizz.a * b + jizz.b * a);
	}
	write(1, outbuf, outp);
	return 0;
}