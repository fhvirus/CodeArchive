#pragma Ofast
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
char ob[65536];
int op;
int main(){
	int n, b, a;
	while((n = R()) != 0){
		b = R();
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n + i - 1; ++j)
				ob[op++] = (j < n - i + 1 ? ' ' : (b == 1 ? '*' : " *"[i == n or j == n - i + 1 or j == n + i - 1]));
			ob[op++] = '\n';
		}
	}
	write(1,ob,op);
	return 0;
}