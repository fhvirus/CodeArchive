#include<cstdio>
long long a[14] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800};
int n;

int main(){
	scanf("%d", &n);
	printf("%lld\n", a[n]);
	return 0;
}