#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n<0)OB[OP++]='-',n=-n;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

int main(){
	long long x, y, z;
	for(int t = R(); t; --t){
		x = R(), y = R(), z = R();
		if(x == 0 and y == 0) W(-1);
		else if(x > 10000) W(0);
		else if(z == 0) W(x == 0 ? 1 : 0);
		else W(((10000 - x) * z) / (10000 + y * z) + 1);
	}
	write(1,OB,OP);
	return 0;
}