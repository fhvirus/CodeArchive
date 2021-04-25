#pragma Ofast
#include<unistd.h>
inline char readchar(){
	static char buf[65536], *p = buf, *q = buf;
	return (p == q and (q = (p = buf) + read(0, buf, 65536)) == buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c < '0') c = readchar();
	while(c >= '0') ans = ans * 10 + (c ^ '0'), c = readchar();
	return ans;
}
#include<cstdio>
long long p[51][51];
inline void init(){
	for(int i = 0; i < 51; ++i) p[i][0] = 1;
	for(int i = 1; i < 51; ++i)
		for(int j = 1; j <= i; ++j)
			p[i][j] = p[i-1][j] + p[i-1][j-1];

	for(int i = 0; i < 51; ++i)
		p[i][0] = 1;
}
int main(){
	init();
	int n, m;
	while(n = R(), m = R(), n != 0) printf("%lld\n", p[n + m - 1][m]);
}