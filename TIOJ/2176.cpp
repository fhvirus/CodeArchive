#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';if(OP>65516)write(1,OB,OP),OP=0;}
#define ll long long
const int N = 1e5 + 225;
int n;
short a[N], b[N];
int sa[N], sb[N];
ll x[N], c[N];

int main(){
	n = R();
	for(int i = 1; i <= n; ++i) a[i] = R();
	for(int i = 1; i <= n; ++i) b[i] = R();
	for(int i = 1; i <= n; ++i){
		for(int j = i; j <= n; j += i){
			sa[i] += a[j];
			sb[i] += b[j];
		}
	}
	for(int i = 1; i <= n; ++i)
		x[i] = (ll)sa[i] * sb[i];
	for(int i = n; i >= 1; --i){
		c[i] = x[i];
		for(int j = 2; i * j <= n; ++j)
			c[i] -= c[i * j];
	}
	for(int i = 1; i <= n; ++i)
		W(c[i]);

	write(1,OB,OP);
	return 0;
}