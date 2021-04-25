#include<cstdio>
int main(){
	int n, m;
	scanf("%d",&n);
	for(m=1;m*2<=n;m*=2);
	printf("%d",(n-m)*2+1)
;}