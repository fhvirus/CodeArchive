#include<cstdio>

long long a[21];

int main(){
	a[1] = 1;
	for(int i = 2; i < 21; ++i){
		a[i] = (4 * i - 2) * a[i-1] / (i + 1);
	}
	int n;
	while(scanf("%d", &n) == 1){
		printf("%lld\n", a[n]);
	}
}