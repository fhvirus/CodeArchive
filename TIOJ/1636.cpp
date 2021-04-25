#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){char OB[20],OP,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

int n, k;
long long a, last;

inline long long max(long long a, long long b){ return a > b ? a : b;}

int main(){
	n = R(), k = R();
	if(n == 1){
		W(1ll * R() * ((k + 1) / 2));
		return 0;
	}

	a = R();
	long long sum = a, ans = a;
	for(int i = 1; i < n and i <= k; ++i){
		last = a;
		a = R();
		sum += a;
		ans = max(ans, sum + last * ((k - i + 1) / 2) + a * ((k - i) / 2));
	}
	W(ans);
	return 0;
}