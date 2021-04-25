#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[30],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,30))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline int jiz(int n, int b){
	int eek = 0;
	while(n){
		eek *= 10;
		eek += n % b;
		n /= b;
	}
	int owo = 0;
	while(eek){
		owo *= 10;
		owo += eek % 10;
		eek /= 10;
	}
	return owo;
}
inline int pow(int x, int e){
	int ans = 1;
	for(; e; --e) ans *= x;
	return ans;
}
int main(){
	int b, n, N;
	b = R(), N = R();
	n = N;
	int d = 0;
	while(n) ++d, n /= 10;
	n = N;
	
	int sum = 0;
	for(int i = 0; i < d; ++i){
		sum += pow(n % 10, d);
		n /= 10;
	}
	if(jiz(sum, b) == N) write(1,"YES",3);
	else write(1,"NO",2);
	return 0;
}
