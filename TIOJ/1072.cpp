#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[4096]; int OP;
inline char RC(){static char buf[4096],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,4096))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>4095)write(1,OB,OP),OP=0;}
inline int max(int a, int b){
	return a > b ? a : b;
}

#define FOR(i,n) for(int i=0;i<n;++i)
const int N = 10000;
int n, ans = 0, curtime = 0;

struct meal{
	int c, e;
} m[N];

#include<algorithm>

int main(){
	while((n = R()) != 0){
		ans = curtime = 0;
		FOR(i,n) m[i] = {R(), R()};
		std::sort(m, m+n, [](meal a, meal b){
			return a.e > b.e;
		});
		for(int i = 0; i < n; ++i){
			curtime += m[i].c;
			ans = max(ans, curtime + m[i].e);
		}
		W(ans);
	}
    write(1,OB,OP);
	return 0;
}
