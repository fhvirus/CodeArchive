#include<cstdio>
int main(){
	int n, k;
	long long ans = 0, i;
	while(scanf("%d%d", &n, &k) != EOF){
		ans = 0;
		if(k != 0) for(i = 1; i <= n; i *= 10){
			int jizz = n / i;
			ans += jizz / 10 * i;
			if(k < jizz % 10) ans += i;
			else if(k == jizz % 10) ans += n % i + 1;
		}
		else for(i = 1; i * 10 <= n; i *= 10){
			int jizz = n / i / 10;
			ans += (jizz - 1) * i;
			if((n / i) % 10) ans += i;
			else ans += n % i + 1;
		}
		printf("%lld\n", ans);
	}
}