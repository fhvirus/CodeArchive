#include<cstdio>
int main(){
	int k, ans = 0, x; scanf("%d", &k);
	for(int i = 0; i <= k; ++i){
		scanf("%d", &x);
		if(ans >= (1<<i) - 1) ans += x * (1<<i);
	}
	printf("%d", ans + 1);
}