#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c==-1)return 0;if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<algorithm>
using namespace std;

const int N = 1e5;
int n, a[N];
int main(){
	while(n = R(), n != 0){
		for(int i = 0; i < n; ++i)
			a[i] = R();
		nth_element(a, a + n / 2, a + n);
		int ans = 0, id = a[n/2];
		for(int i = 0; i < n; ++i)
			ans += abs(a[i] - id);
		W(ans);
	}
	write(1,OB,OP);
	return 0;
}