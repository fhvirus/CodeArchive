#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<unistd.h>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}

char outbuf[S];
int outp;

int n;
int main(){
	while((n = R()) != 0){
		for(int i = 0; i < n - 1; ++i){
			for(int j = 0; j < (2 * n - 1) - i; ++j){
				outbuf[outp++] = (j == i or j == n-1 or j + i == n * 2 - 2 ? '*' : ' ');
			}
			outbuf[outp++] = ('\n');
		}
		for(int i = 0; i < 2 * n - 1; ++i)
			outbuf[outp++] = ('*');
		outbuf[outp++] = ('\n');
		for(int i = n-2; i >= 0; --i){
			for(int j = 0; j < (2 * n - 1) - i; ++j){
				outbuf[outp++] = (j == i or j == n-1 or j + i == n * 2 - 2 ? '*' : ' ');
			}
			outbuf[outp++] = ('\n');
		}
		write(1, outbuf, outp);
		outp = 0;
	}
}