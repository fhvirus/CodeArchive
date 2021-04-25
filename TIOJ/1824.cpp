#include<unistd.h>
char ib[10], *ip = ib, OB[30], OP;
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';}
int a, p, jizz, eek;
char e;
int main(){
	read(0,ib,10);
	while((*ip) >= '0') a *= 10, ((*ip)=='?') ? (p=1) : (a += (*ip) - '0'), p *= 10, ip++;
	jizz = (a%7);
	a += jizz * p / 10, W(a);
	if(jizz < 3) W(a + 7 * p / 10);
	write(1,OB,OP);
}