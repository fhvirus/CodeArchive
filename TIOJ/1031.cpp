#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

int a;
int ans;
bool jizz = true;
int main(){
	while(true){
		a = R();
		if(a == 0 and jizz) break;
		if(a == 0) W(ans), ans = 0, jizz = true;
		else jizz = false, ans += 1 << (31 - __builtin_clz(a));
	}
	write(1,OB,OP);
}