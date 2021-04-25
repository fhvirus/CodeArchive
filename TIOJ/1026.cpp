#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>

int main(){
	int d, jizz;
	scanf("%d", &d);
	jizz = 32 - __builtin_clz(d);
	printf("%d\n", jizz);
	int eek = ((1<<jizz) - d)>>1;
	for(int i = 0; i < jizz; ++i){
		putchar(eek&(1<<i) ? '-' : '+');
	} 
}