#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=1;i<=n;++i)
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0'&&c!=EOF) c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
inline int G(){
	char c = readchar();
	while(c < '0' and c != EOF) c = readchar();
	return c - '0';
}
char outbuf[S];
int outp;

int r, c, a[102][102];

int main(){
	while(r = R(), c = R(), r != 0){
		FOR(i, r) FOR(j, c) a[i][j] = G();
		FOR(i, r + 1) a[i][c + 1] = 0;
		FOR(i, c + 1) a[r + 1][i] = 0;
		FOR(i, r){
			FOR(j, c)
				outbuf[outp++] = (
					a[i][j] == 1 ? 'X' :
					(a[i-1][j-1] + a[i-1][j] + a[i-1][j+1] + a[i][j-1] + a[i][j+1] + a[i+1][j-1] + a[i+1][j] + a[i+1][j+1] + '0')
				), outbuf[outp++] = ' ';
			outbuf[outp++] = '\n';
			if(outp > S - 200) fwrite(outbuf, 1, outp, stdout), outp = 0;
		}
	}
	fwrite(outbuf, 1, outp, stdout);
}