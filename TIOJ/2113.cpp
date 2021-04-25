#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[512]; int OP;
inline char RC(){static char buf[512],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,512))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(long long n){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>492)write(1,OB,OP),OP=0;}


int t, n;
long long sum;
int main(){
	t = R();
	for(; t; --t){
		n = R(), sum = 0;
		for(; n; --n) sum += R();
		W(sum);
	}
	write(1,OB,OP);
}