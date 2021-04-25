#include<unistd.h>
char OB[9999]; int OP;
inline char RC(){static char buf[9999],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,9999))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n, char e){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>9979)write(1,OB,OP),OP=0;}

int jizz, first, sum, cnt;

int main(){
	while((sum = first = R()) != 0){
		cnt = 1;
		while((jizz = R()) != 0) sum += jizz, ++cnt;
		W(first, ' '), W(cnt, ' '), W(sum, '\n');
	}
	write(1,OB,OP);
}