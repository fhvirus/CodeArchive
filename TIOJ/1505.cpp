#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>

int main(){
	int T, n;
	long long num, den;
	for(T=R();T;--T){
		n = R()-2; num = R(); den = R();
		for(num %= den; num && n; --n){
			num = num * (long long)R() % den;
		}
		for(; n; --n) R();
		puts(num == 0 ? "Asssss!!" : "zzz...");
	}
	return 0;
}