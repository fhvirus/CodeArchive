#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<algorithm>
const int N = 1e7+1;
bool isprime[N];
int primes[664579], e;
int main(){
	isprime[0] = isprime[1] = true;
	for(int i = 2; i < N; ++i){
		if(!isprime[i]) primes[e++] = i;
		for(int p = 0; p < e; ++p){
			if(i * primes[p] > N) break;
			isprime[i * primes[p]] = true;
			if(i % primes[p] == 0) break;
		}
	}
	for(int t = R(), n; t; --t){
		n = R();
		W(std::upper_bound(primes, primes+e, n) - primes);
	}
	write(1,OB,OP);
	return 0;
}