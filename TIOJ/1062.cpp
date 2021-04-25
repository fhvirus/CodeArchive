#pragma Os
#pragma loop_opt(on)
#include<unistd.h>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 10000;
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans=0; char c=readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[8], outp;

const int N = 100;
int m, n, a, sumi[N], sumj[N];
int main(){
	m = R(), n = R();
	FOR(i, m) FOR(j, n)
		a = R(), sumi[i] += a, sumj[j] += a;

	int total = 0;
	FOR(i, m) total += sumi[i];
	int cursum = 0, i, j;
	for(i = 0; i < m; ++i){
		cursum += sumi[i];
		if(cursum >= (total + 1) / 2){
			++i; break;
		}
	}
	if(i >= 100) outbuf[outp++] = '1';
	if(i >= 10) outbuf[outp++] = i % 100 / 10 + '0';
	outbuf[outp++] = i % 10 + '0';
	outbuf[outp++] = ' ';

	cursum = 0;
	for(j = 0; j < n; ++j){
		cursum += sumj[j];
		if(cursum >= (total + 1) / 2){
			++j;
			break;
		}
	}
	if(j >= 100) outbuf[outp++] = '1';
	if(j >= 10) outbuf[outp++] = j % 100 / 10 + '0';
	outbuf[outp++] = j % 10 + '0';
	write(1, outbuf, outp);
	return 0;
}