#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n, char e){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}

#include<unordered_map>
int n, mode, modetimes;
std::unordered_map<int, int> eek;
int main(){
	while((n = R()) != 0){
		int *t = &eek[n];
		if(++(*t) > modetimes) modetimes = *t, mode = n;
		if(*t == modetimes) mode = mode < n ? mode : n;
		W(modetimes, ' '), W(mode, '\n');
	}
	write(1,OB,OP);
}