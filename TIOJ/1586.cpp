#include<cstdio>
int n;
char eek[60];
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; ++i){
		scanf("%s", eek);
		printf("%s, happy new year!!!\n", eek);
	}
}