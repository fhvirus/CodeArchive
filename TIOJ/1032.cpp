#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
const int N = 1e5;
int n, m;
unsigned h[N];
inline void add(int a, int b){
	if(a > b) a ^= b, b ^= a, a ^= b;
	unsigned jizz = (a * 13 + b);
	h[a] += jizz;
	h[b] -= jizz;
}
inline void sub(int a, int b){
	if(a > b) a ^= b, b ^= a, a ^= b;
	unsigned jizz = (a * 13 + b);
	h[b] += jizz;
	h[a] -= jizz;
}
inline void jizz(){
	unsigned sum = 0;
	int k = R();
	for(; k; --k)
		sum = (sum + h[R()]);
	puts(sum == 0 ? "1" : "0");
}

int main(){
	n = R(), m = R();
	for(int cmd; m; --m)
		(cmd = R()) == 0 ? add(R(), R()) : (cmd == 1 ? sub(R(), R()) : jizz());
}