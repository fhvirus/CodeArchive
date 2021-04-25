#include<cstdio>
#define MAXN 100005
int gen[MAXN];
int digsum(int n){
	int sum=0;
	while(n>0)sum+=n%10,n/=10;
	return sum;
}
int main(){
	for(int i=0;i<MAXN;i++)gen[i]=digsum(i)+i;
	int n,in,j;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&in);
		for(j=0;j<MAXN;j++)if(gen[j]==in)break;
		printf("%d\n",j==MAXN?0:j);
	}
	return 0;
}