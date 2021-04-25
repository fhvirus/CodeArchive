#include<cstdio>

int main(){
	int a, b, ans = 0;
	scanf("%d %d", &a, &b);
	while(a != b){
		(a > b ? a : b) >>= 1;
		++ans;
	}
	printf("%d\n", ans);
}