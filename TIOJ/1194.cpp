#pragma GCC optimize("Os")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[25502],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,25502))==buf?-1:*p++;}

int main(){
	char c;
	while(RC() != '0'){
		while(RC() != ' ');
		while((c = RC()) != ' ') OB[OP++] = c;
		OB[OP++] = '\n';
		while(RC() != '\n');
	}
	write(1,OB,OP);
}