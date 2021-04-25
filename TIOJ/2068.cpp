#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n, char e){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}

const int N = 2345678;
int n;
bool np[N*4], vis[N*2];
int primes[626323], owo;
int main(){
	n = R();

	np[0] = np[1] = true;
	for(int i = 2; i < 4*n; ++i){
		if(!np[i]) primes[owo++] = i;
		for(int p = 0; p < owo; ++p){
			if(i * primes[p] >= 4*n) break;
			np[i * primes[p]] = true;
			if(i % primes[p] == 0) break;
		}
	}

	for(int i = 0; i < 2 * n; ++i){
		if(vis[i]) continue;
		for(int j = i + 1; j < 2 * n; j += 2)
			if(!vis[j] and !np[4 * n - i - j]){
				vis[i] = true, vis[j] = true;
				W(i, ' '), W(j, '\n');
				break;
			}
	}
	write(1,OB,OP);
	return 0;
}