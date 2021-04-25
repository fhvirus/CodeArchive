#pragma GCC optimize("Os")
#include<unistd.h>
inline char RC(){static char buf[256],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,256))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
#include<algorithm>
int n, a, ans, bucket[200], p = 199;
int main(){
	n = R();
	bucket[199] = R();
	for(int i = 1; i < n; ++i)
		a = R(), (bucket[p] < a ? *(std::lower_bound(bucket + p, bucket + 200, a) - 1) : bucket[--p]) = a;
	p = 200 - p;
	char ob[4], op = 0;
	if(p >= 100) ob[op++] = p / 100 + '0';
	if(p >= 10) ob[op++] = p % 100 / 10 + '0';
	ob[op++] = p % 10 + '0';
	write(1,ob,op);
}