#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
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
inline bool isAlpha(char eek){
	return (eek <= 'Z' and eek >= 'A') or (eek <= 'z' and eek >= 'a');
}
char outbuf[1<<20];
int outp;

int main(){
	int n, k;
	char eek;
	while(true){
		n = R(); k = R();
		if(n == 0) break;
		k = n - k;

		FOR(i,k){
			while(!isAlpha(readchar()));
			while(readchar() != '\n');
		}

		while(!isAlpha(eek = readchar()));
		outbuf[outp++] = eek;
		while(isAlpha(eek = readchar()))
			outbuf[outp++] = eek;
		outbuf[outp++] = '\n';
		if(outp > (1<<20) - 128) fwrite(outbuf, 1, outp, stdout), outp = 0;
	}
	fwrite(outbuf, 1, outp, stdout);
}