#pragma Os
#include<cstdio>
int R(){
	int ans = 0; char c = getchar_unlocked();
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=getchar_unlocked();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=getchar_unlocked();
	return ans;
}

int n, a, l[20], i, j;

int main(){
	while((n = R()) != 0){
		for(i = 0; i < 20; ++i) l[i] = 0;
		for(i = 0; i < n; ++i){
			a = R();
			for(j = 31 - __builtin_clz(a); a != 0; j = 31 - __builtin_clz(a)){
				if(!l[j]){ l[j] = a; break;}
				a ^= l[j];
			}
		}
		a = 0;
		for(i = 19; i >= 0; --i)
			a = (a >= (a^l[i]) ? a : a ^= l[i]);

		if(a >= 1000000) putchar_unlocked(a / 1000000 + '0');
		if(a >= 100000) putchar_unlocked(a % 1000000 / 100000 + '0');
		if(a >= 10000) putchar_unlocked(a % 100000 / 10000 + '0');
		if(a >= 1000) putchar_unlocked(a % 10000 / 1000 + '0');
		if(a >= 100) putchar_unlocked(a % 1000 / 100 + '0');
		if(a >= 10) putchar_unlocked(a % 100 / 10 + '0');
		putchar_unlocked(a % 10 + '0');
		putchar_unlocked('\n');
	}
	return 0;
}