#include<cstdio>
char keys[]="`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
int main(){
	int i,c;
	while((c=getchar())!=EOF){
		for(i=1;keys[i]&&keys[i]!=c;i++);
		if(keys[i])putchar(keys[i-1]);
		else putchar(c);
	}
	return 0;
}