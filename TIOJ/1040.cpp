#pragma GCC optimize("Os")
#include<unistd.h>
char OB[16384]; int OP;
inline char RC(){static char buf[16384],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,16384))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];if(OP>16344)write(1,OB,OP),OP=0;}

void solve(int a, int b){
	if(a % b == 0){ W(a/b); return;}
	OB[OP++] = '{'; W(a/b);
	OB[OP++] = '+'; OB[OP++] = '1'; OB[OP++] = '/';
	solve(b, a%b);
	OB[OP++] = '}';
}

int main(){
	for(int n = R(), a, b; n; --n){
		a = R(), b = R();
		W(a); OB[OP++] = '/';
		W(b); OB[OP++] = ' '; OB[OP++] = '='; OB[OP++] = ' ';
		W(a/b);
		if(a%b){
			OB[OP++] = '+'; OB[OP++] = '1'; OB[OP++] = '/';
			solve(b, a%b);
		}
		OB[OP++] = '\n';
	}
	write(1,OB,OP);
	return 0;
}