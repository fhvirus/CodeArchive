#include<cstdio>
#include<string.h>
#define MAXN 85
int main(){
	char s[MAXN];
	int n;
	scanf("%d",&n);
	while(n--){
		scanf("%s",s);
		int len=strlen(s),cnt=0,ans=0;
		for(int i=0;i<len;i++){
			if(s[i]=='O')ans+=++cnt;
			else cnt=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}