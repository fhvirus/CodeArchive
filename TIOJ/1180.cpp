#include<cstdio>
long long a[14] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800};
int t, n;

int main(){
	scanf("%d", &t);
	for(int i = 1; i <= t; ++i){
		scanf("%d", &n);
		printf("Case #%d:\n", i);
		for(int i = 0; i <= n; ++i){
			printf("TFCIS%d=%lld\n", i, a[i]);
		}
	}
	return 0;
}