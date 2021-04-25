#pragma GCC optimize("Ofast")
#include<unistd.h>
const int S = 20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
char outbuf[3] = {'Y', 'e', 's'};
int main(){
	int m = 0, n = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') m=(m*10)+(c^'0'), c=readchar();
	while(c<'0') c=readchar();
	while(c>='0') n=(n*10)+(c^'0'), c=readchar();
	outbuf[0] = (n > m*(m-1)>>1 ? 'Y' : 'y');
	write(1, outbuf, 3);
	return 0;
}