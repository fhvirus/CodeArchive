#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#include<cmath>

int main(){
	int a, ans;
	while(scanf("%d", &a) != EOF){
		if(a < 0){ puts("stupid"); continue;}
		a *= 100;
		ans = a / 101 + (a % 101 ? 1 : 0);
		if(ans > 1024 or ans < 0){ puts("stupid"); continue;}
		printf("%d\n", ans);
	}
}