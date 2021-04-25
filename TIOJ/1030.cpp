#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(long long int n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

int n, a, mx;
long long sum;
inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	while((n = R()) != 0){
		sum = mx = 0;
		for(; n; --n)
			sum += (a = R()), mx = mx > a ? mx : a;
		W(sum + mx + 1);
	}
	fwrite(outbuf, 1, outp, stdout);
}