#pragma GCC optimize("Os")
#include<unistd.h>
inline char RC(){static char buf[4096],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,4096))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
char OB[4096]; int OP = 0;
inline void putchar(char a){ OB[OP++] = a; if(OP > 4095) write(1, OB, OP), OP = 0;}

int n, m;
int frac[13] = {1};
bool yes[12];

int main(){
	for(int i = 1; i <= 12; ++i)
		frac[i] = frac[i-1] * i;
	while((n = R()) != 0){
		m = (R() - 1) % frac[n];
		for(int i = 0; i < 12; ++i)
			yes[i] = false;
		for(int i = n, a; i > 0; --i){
			a = m / frac[i-1] + 1;
			int cnt = 0, j = 0;
			for(; j < n; ++j){
				if(cnt == a) break;
				cnt += !yes[j];
			}
			putchar('A' + j - 1);
			putchar(' ');
			yes[j - 1] = true;
			m %= frac[i-1];
		}
		putchar('\n');
	}
	write(1,OB,OP);
}