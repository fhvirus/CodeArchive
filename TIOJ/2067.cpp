#include<cstdio>
int main(){
	int k;
	scanf("%d", &k);
	for(int i = 1; i <= k; ++i){
		for(int j = 1; j <= (1<<i)-1; ++j)
			putchar_unlocked(31 - __builtin_clz(j & -j) + 'a');
		putchar_unlocked('\n');
	}
}