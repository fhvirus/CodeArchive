#pragma GCC optimize("Os")
#include<unistd.h>
inline char RC(){static char buf[20],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,20))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
int main(){
	int a = R(), b = R(), c = R();
	bool jiz = (c + a == b + b);
	bool eek = (c * a == b * b and a != 0 and b != 0 and c != 0);
	if(jiz and eek) write(1,"both",4);
	if(jiz and !eek) write(1,"arithmetic",10);
	if(!jiz and eek) write(1,"geometric",9);
	if(!jiz and !eek) write(1,"normal",6);
}