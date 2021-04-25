#pragma Os
#include<cstdio>
#include<cmath>
const int N = 100000;
char a[N]; int l = 0; double ans = 0, jizz = 1;
int main(){
	fread(a, 1, N, stdin); while(a[l] >= '0' and a[l] <= '9') ++l; a[l] = '\0';
	for(int i = 0; i < l and i < 10; jizz *= 0.1, ++i) ans += (a[i] - '0') * jizz;
	l = (log(ans) / log(2) + (l - 1) * log(10) / log(2));
	if(l >= 100000) putchar_unlocked(l / 100000 + '0');
	if(l >= 10000) putchar_unlocked(l % 100000 / 10000 + '0');
	if(l >= 1000) putchar_unlocked(l % 10000 / 1000 + '0');
	if(l >= 100) putchar_unlocked(l % 1000 / 100 + '0');
	if(l >= 10) putchar_unlocked(l % 100 / 10 + '0');
	putchar_unlocked(l % 10 + '0');
}