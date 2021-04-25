#include<cstdio>
int main(){
	char c;
	bool f=0;
	while((c=getchar())!=EOF){
		if(c=='"'){printf("%s",f?"''":"``");f=!f;}
		else printf("%c",c);
	}
	return 0;
}