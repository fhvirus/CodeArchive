#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<unistd.h>
const int S = 1<<12;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0' and c != -1) c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(long long n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) write(1, outbuf, outp), outp = 0;
}
inline int min(int a, int b){
	return a < b ? a : b;
}
int n, r[501], b[501];
long long ans;

int main(){
	while((n = R()) != 0){
		ans = 0;
		for(int i = 0; i <= 500; ++i) r[i] = b[i] = 0;
		for(int i = 0; i < n; ++i) ++r[R()];
		for(int i = 0; i < n; ++i) ++b[R()];
		int i = 500, j = 1, jizz;
		while(n > 0){
			while(i > 0 and r[i] == 0) --i;
			while(j <= 500 and b[j] == 0) ++j;
			jizz = min(r[i], b[j]);
			ans += 1ll * i * j * jizz, r[i] -= jizz, b[j] -= jizz, n -= jizz;
		}
		W(ans);
	}
	write(1, outbuf, outp);
}