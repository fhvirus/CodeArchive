#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[2048]; int OP;
inline char RC(){static char buf[2048],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,2048))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';if(OP>2028)write(1,OB,OP),OP=0;}

int t, n, m, u, v, a;
int main(){
	for(t = R(); t; --t){
		for(n = R() - 1, m = R(), u = 1e9, v = -1e9; n; --n){
			a = R();
			u = (a > m and u > a) ? a : u;
			v = (a < m and v < a) ? a : v;
		}
		W(u), W(v), OB[OP++] = '\n';
	}
	write(1, OB, OP);
}