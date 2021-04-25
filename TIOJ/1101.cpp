#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<unistd.h>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0, buf, S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=ans*10+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n, char e){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = e;
    if(outp > S-15) write(1, outbuf, outp), outp = 0;
}

struct frac{
	int a, b;
	frac operator+(const frac &rhs){
		return {a + rhs.a, b + rhs.b};
	}
};
int n, k;

int main(){
	while(n = R(), k = R(), n != 0){
		if(n == 1){ k == 1 ? (W(0, '/'), W(1, '\n')) : (W(1, '/'), W(0, '\n')); continue;}

		frac l = {0, 1}, r = {1, 0}, m;
		int lptr = 0, rptr = 1<<(n-2), mptr;
		for(int i = 2; i < n; ++i){
			m = l + r;
			mptr = (lptr + rptr) / 2;
			if(k <= mptr) r = m, rptr = mptr;
			else l = m, lptr = mptr;
		}
		m = l + r;
		W(m.a, '/');
		W(m.b, '\n');
	}
	write(1, outbuf, outp);
}