#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline short R(){
	short ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=ans*10+(c^'0'), c=readchar();
	return ans;
}

inline int gcd(int a, int b){
	while(b){
		a %= b;
		a ^= b ^= a ^= b;
	}
	return a;
}

int n, a, g;
int main(){
	n = R();
	for(; n; --n)
		g = gcd(R(), g);
	printf("%d", g);
}