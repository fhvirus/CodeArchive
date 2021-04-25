#include<cstdio>
#include<string.h>
#define MAXN 105
bool less(const char* s,int a,int b){
	int n=strlen(s);
	for(int i=0;i<n;i++)
		if(s[(a+i)%n]!=s[(b+i)%n])return s[(a+i)%n]<s[(b+i)%n];
	return 0;
}
int main(){
	int n;
	char s[MAXN];
	scanf("%d",&n);
	while(n--){
		scanf("%s",s);
		int ans=0,len=strlen(s);
		for(int i=1;i<len;i++)
			if(less(s,i,ans))ans=i;
		for(int i=0;i<len;i++)
			putchar(s[(ans+i)%len]);
		putchar('\n');
	}
	return 0;
}