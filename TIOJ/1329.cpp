#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';if(OP>65516)write(1,OB,OP),OP=0;}

#define FOR(i,n) for(int i=0;i<n;++i)
inline int abs(int a){ return a < 0 ? -a : a;}

const int N = 1000;

int t, n;
short a[N], ans[N], anspos[N];

int main(){
	t = R();
	for(; t; --t){
		n = R();
		FOR(i, n) a[i] = R(), ans[i] = 0, anspos[i] = i;
		FOR(i, n){
			for(int j = i+1, jizz; j < n; ++j){
				jizz = (j - i == 1) ?
				(i > 0 ? abs(a[j] - a[i-1]) - abs(a[i] - a[i-1]) : 0) + (j < n-1 ? abs(a[i] - a[j+1]) - abs(a[j] - a[j+1]) : 0)
				:
				((i > 0 ? abs(a[j] - a[i-1]) - abs(a[i] - a[i-1]) : 0)
			   	+ (i < n-1 ? abs(a[j] - a[i+1]) - abs(a[i] - a[i+1]) : 0)
			   	+ (j > 0 ? abs(a[i] - a[j-1]) - abs(a[j] - a[j-1]) : 0)
			   	+ (j < n-1 ? abs(a[i] - a[j+1]) - abs(a[j] - a[j+1]) : 0));
				if(jizz < ans[i]) ans[i] = jizz, anspos[i] = j;
				if(jizz < ans[j] or (jizz == ans[j] and i < anspos[j])) ans[j] = jizz, anspos[j] = i;
			}
		}
		FOR(i, n) W(anspos[i]+1);
		OB[OP++] = '\n';
	}
	write(1,OB,OP);
}