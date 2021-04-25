#pragma Ofast
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
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
    if(outp > S-15) write(1, outbuf, outp), outp = 0;
}

int n, m;
long long k;
int main(){
	while(n = R(), m = R(), k = R(), n != 0){
		if(m == 1){ W(n - k); continue;}
		k = n - k - 1;
		for(k = k * m + m - 1; k >= n; k = k - n + (k - n) / (m - 1));
		W(k + 1);
	}
	write(1, outbuf, outp);
	return 0;
}