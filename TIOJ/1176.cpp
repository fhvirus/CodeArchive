#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0){outbuf[outp++] = '0'; outbuf[outp++] = '\n'; return;}
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
    if(outp > S-15) fwrite(outbuf, 1, outp, stdout), outp = 0;
}

#define FOR(i,n) for(int i=0;i<n;++i)
#define MAXN 1000000
int n, a[MAXN], ans[MAXN], top;
struct cow{
	int h, id;
} cows[MAXN];

int main(){
	n = R();
	FOR(i,n) a[i]=R();
	for(int i = n-1; i >= 0; --i){
		while(top != 0 and cows[top-1].h <= a[i]) --top;
		if(top == 0) ans[i] = n - i - 1;
		else ans[i] = cows[top-1].id - i;
		cows[top++] = {a[i], i};
	}
	FOR(i,n) W(ans[i]);
	fwrite(outbuf, 1, outp, stdout);
	return 0;
}