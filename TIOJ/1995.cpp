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
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
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

inline int max(int a, int b){
	return a > b ? a : b;
}

const int N = 1e6;
int n, m, l[N], r[N], a[2500000];

int main(){
	n = R(); m = R();
	for(int i = 0; i < m; ++i) l[i] = R()-1, r[i] = R()-1;
	for(int i = 0; i < n; ++i) a[i] = R();
	for(int q = 0; q < m; ++q) if(l[q] == r[q]) l[q] = a[l[q]], r[q] = -1;
	for(int len = 1; (1<<len) <= n; ++len){
		for(int i = 0; i + (1<<len) <= n; ++i)
			a[i] = max(a[i], a[i+(1<<(len-1))]);
		for(int q = 0; q < m; ++q)
			if(r[q] != -1 && 31 - __builtin_clz(r[q] - l[q] + 1) == len)
				l[q] = max(a[l[q]], a[r[q] - (1<<len) + 1]), r[q] = -1;
	}
	for(int q = 0; q < m; ++q) W(l[q]);
	fwrite(outbuf, 1, outp, stdout);
	return 0;
}