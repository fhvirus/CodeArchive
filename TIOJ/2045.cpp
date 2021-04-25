#pragma Os
#include<cstdio>
inline int R(){
	int ans = 0; char c=getchar_unlocked();
	while(c<'0') c=getchar_unlocked();
	while(c>='0') ans=(ans*10)+(c^'0'), c=getchar_unlocked();
	return ans;
}
int main(){
	int n, m;
	n = R(), m = R();
	if(m == (long long)n * (n-1) / 2){putchar_unlocked('0'); return 0;}
	char eek[10], eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) putchar_unlocked(eek[eekp]);
}