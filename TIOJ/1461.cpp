#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}
char outbuf[S];
int outp;

const int N = 1e7 + 1;
char s[N], eek;
int n, m, p;

int main(){
	while((n = R()) != 0){
		m = R(); p = 0;
		eek = readchar();
		while(eek > 'z' or eek < 'a') eek = readchar();
		for(int i = 0;; ){
			s[p] = eek;
			++(eek == '\n' ? i : p);
			if(i == n) break;
			eek = readchar();
		}
		for(int a; m; --m)
			outbuf[outp++] = s[R()-1];
		outbuf[outp++] = '\n';
		if(outp > S - 101) fwrite(outbuf, 1, outp, stdout);
	}
	fwrite(outbuf, 1, outp, stdout);
}