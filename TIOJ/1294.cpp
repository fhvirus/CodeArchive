#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
int main(){
	char c;
	while((c = RC()) != -1){
		if(c == '\n' or c == ' ') continue;
		if(c == '1' or c == '4') OB[OP++] = '1';
		if(c == '2') OB[OP++] = '9';
		if(c == '3') OB[OP++] = '8', OB[OP++] = '3';
		OB[OP++] = '\n';
	}
	write(1,OB,OP);
}