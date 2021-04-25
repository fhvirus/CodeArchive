#include<cstdio>
int main(){
	int a, b;
	scanf("%d%d", &a, &b);
	puts((a > b ? a : b)%(a < b ? a : b) == 0 ? "Y" : "N");
	return 0;
}