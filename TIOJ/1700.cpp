#pragma Ofast
#include<unistd.h>
inline char readchar(){
	static char buf[65536], *p = buf, *q = buf;
	return (p == q and (q = (p = buf) + read(0, buf, 65536)) == buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c < '0' and c != -1) c = readchar();
	while(c >= '0') ans = ans * 10 + (c ^ '0'), c = readchar();
	return ans;
}
inline int gcd(int a, int b){
	while(b)
		a %= b, a ^= b, b ^= a, a ^= b;
	return a;
}
#include<cstdio>
int main(){
	int n, a, ans;
	while((n = R()) != 0){
		ans = 0;
		for(; n; --n)
			a = R(), ans = gcd(ans, a);
		printf("%d\n", ans);
	}
}