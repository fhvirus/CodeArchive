#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return -1;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(bool n){OB[OP++] = (n ? '+' : '-'); OB[OP++] = '1'; OB[OP++] = ' ';}

bool walsh(int n, int i, int j){
	if(n == 0) return false;
	return (i >= (1<<(n-1)) and j >= (1<<(n-1))) ^ walsh(n-1, i % (1<<(n-1)), j % (1<<(n-1)));
}
int main(){
	int n, i, a, b;
	while((n = R()) != -1){
		i = R() - 1; a = R() - 1; b = R() - 1;
		for(int j = a; j <= b; ++j) W(walsh(n, i, j));
		OB[OP++] = '\n';
		if(OP > 65500) write(1,OB,OP), OP = 0;
	}
	write(1,OB,OP);
	return 0;
}
