#include<cstdio>
#include<cstring>

char s[101], len, ans;
bool flag;

bool check(){
	for(int i = 0; i < len; ++i)
		if(s[i] != s[i%ans]) return false;
	return true;
}

int main(){
	int jizz = 0;
	while(scanf("%s", s) != EOF){
		len = strlen(s);
		flag = false;
		for(ans = 1; ans <= len>>1; ++ans){
			if(len % ans != 0) continue;
			if(check()){ flag = true; break;}
		}
		if(!flag) puts("1");
		else printf("%d\n", len / ans);
	}
	return 0;
}