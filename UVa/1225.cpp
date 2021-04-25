#include<cstdio>
#include<string.h>
int main(){
	int n,T,cnt[10],tmp;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(cnt,0,sizeof(cnt));
		for(int i=1,tmp=1;i<=n;tmp=++i){
			while(tmp>0)cnt[tmp%10]++,tmp/=10;
		}
		for(int i=0;i<10;i++)printf(i==9?"%d":"%d ",cnt[i]);
		printf("\n");
	}
	return 0;
}