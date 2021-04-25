#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c==-1)return 0;if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n, char e){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}
#define FOR(i,n) for(int i = 0; i < n; ++i)
const int N = 1e6;
int n, a[N];

#include<algorithm>

int main(){
	while((n = R()) != 0){
		FOR(i,n) a[i] = R();
		std::sort(a, a + n);
		FOR(i,n) W(a[i], " \n"[i == n-1]);
	}
	write(1,OB,OP);
}