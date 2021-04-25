#include<cstdio>
int main(){
	int n,a[1010],b[1010];
	int game=0;
	while(scanf("%d",&n)==1&&n){
		printf("Game %d:\n",++game);
		for(int i=0;i<n;i++)scanf("%d",&a[i]);
		for(;;){
			int A=0,B=0;
			bool f=true;
			for(int i=0;i<n;i++){
				scanf("%d",&b[i]);
				if(a[i]==b[i])A++;
				if(b[i])f=0;
			}
			if(f)break;
			for(int num=1;num<=9;num++){
				int cnta=0,cntb=0;
				for(int i=0;i<n;i++){
					if(a[i]==num)cnta++;
					if(b[i]==num)cntb++;
				}
				B+=(cnta<cntb?cnta:cntb);
			}
			printf("    (%d,%d)\n",A,B-A);
		}
	}
	return 0;
}