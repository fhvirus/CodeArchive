#include<cstdio>
#include<cmath>
int main(){
	int n;
	while(scanf("%d", &n) != -1){
		printf("%d\n", (int)log10(n) + 1);
	}
	return 0;
}