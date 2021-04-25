#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<algorithm>
using namespace std;
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<16;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c=readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
inline void Rx(char s[]){
	while((s[0]=readchar())!='#');
	s[0] = readchar();
	s[1] = readchar();
	s[2] = readchar();
	s[3] = readchar();
	s[4] = readchar();
	s[5] = readchar();
}

const int N = 1000000;
char code[N][7];
int col[N], row[N];
char t;
int m, n, q, ar, ac, br, bc;

char outbuf[1<<24];
int outp = 0;

int main(){
	m = R(), n = R();
	for(int i = 0, x = m*n; i < x; ++i)
		Rx(code[i]);
	FOR(i,m) row[i] = i;
	FOR(i,n) col[i] = i;
	for(q = R(); q; --q){
		while((t=readchar())!='S'&&t!='R'&&t!='C');
		if(t == 'S'){
			ar = R()-1; ac = R()-1; br = R()-1; bc = R()-1;
			if(!(ar==br && ac==bc))
				swap(code[row[ar]*n+col[ac]], code[row[br]*n+col[bc]]);
		} else if(t == 'R'){
			ar = R()-1; br = R()-1;
			if(ar != br) swap(row[ar], row[br]);
		} else {
			ac = R()-1; bc = R()-1;
			if(ac != bc) swap(col[ac], col[bc]);
		}
	}
	int idx;
	FOR(i,m){
		FOR(j,n){
			idx = row[i]*n+col[j];
			outbuf[outp] = '#';
			outbuf[outp+1] = code[idx][0];
			outbuf[outp+2] = code[idx][1];
			outbuf[outp+3] = code[idx][2];
			outbuf[outp+4] = code[idx][3];
			outbuf[outp+5] = code[idx][4];
			outbuf[outp+6] = code[idx][5];
			outbuf[outp+7] = ' ';
			outp += 8;
		}
		outbuf[outp++] = '\n';
	}
	fwrite(outbuf, outp, 1, stdout);
	return 0;
}