#include<cstdio>
#include<string.h>
#include<cctype>
#define MAXN 85
double mass(char c){return (c=='C'?12.01:(c=='H'?1.008:(c=='O'?16.000:14.010)));}
int main(){
	int T;
	char chem[MAXN];
	scanf("%d",&T);
	while(T--){
		scanf("%s",chem);
		int len=strlen(chem),x;
		double ans=0;
		for(int i=0;i<len;i++){
			if(isalpha(chem[i])){
				if(i<len-1&&isdigit(chem[i+1])){
					if(i<len-2&&isdigit(chem[i+2]))x=(chem[i+1]-'0')*10+chem[i+2]-'0';
					else x=chem[i+1]-'0';
				}else x=1;
				ans+=x*mass(chem[i]);
			}
		}
		printf("%.3f\n",ans);
	}
	return 0;
}

//12.010 1.008 16.000 14.010