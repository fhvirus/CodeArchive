#pragma Ofast
#include<unistd.h>
inline char RC(){static char buf[12],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,12))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n<0)n=-n,OB[OP++]='-';if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int eek[6] = {-1, -1, 2, 5, 5, 2};
inline int h(int x){
	return x < 2 ? -1 : eek[x % 6];
}
inline int g(int x){
	return x <= 2 ? x * x - 1 : 2;
}
inline int f(int x){
	int jiz = h(x);
	if(x == jiz) return 1;
	return x > jiz ? f(x-1) - h(x) : f(g(x)) - g(x);
}

int main(){
	W(f(R()));
}