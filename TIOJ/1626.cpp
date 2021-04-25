#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<unistd.h>
#include<vector>
#include<bitset>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p == q and (q = (p = buf) + read(0, buf, S)) == buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c < '0') c = readchar();
	while(c >= '0') ans = ans * 10 + (c ^ '0'), c = readchar();
	return ans;
}
inline long long g(long long n){
	return n == 1 ? 1 : 1 + g(n - g(g(n-1)));
}

#include<cmath>
const long double PHI = (1 + sqrtl(5)) / 2;
int n;
int main(){
	while((n = R() + 1) != 1){
		printf("%d\n", (int)(powl(PHI, 2 - PHI) * powl(n, PHI-1)));
	}
}