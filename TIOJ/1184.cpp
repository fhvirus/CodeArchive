#pragma GCC optimize("Os")
#include<unistd.h>
char OB[500]; int OP;
inline char RC(){static char buf[500],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,500))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;
	if(n == -1){
		OB[OP++] = 's';
		OB[OP++] = 'o';
		OB[OP++] = ' ';
		OB[OP++] = 's';
		OB[OP++] = 'a';
		OB[OP++] = 'd';
	}
	else{
		if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];
	}
	OB[OP++]='\n';
	if(OP>480)write(1,OB,OP),OP=0;
}

#include<algorithm>
using namespace std;

const int N = 200;
int t, n, m;
#pragma GCC pack(1)
struct owo{
	int c; short n;
	bool operator<(const owo &rhs) const{
		return c < rhs.c;
	}
} a[N];
#pragma GCC pack()

int main(){
	for(t = R(); t; --t){
		n = R(), m = R();
		for(int i = 0; i < n; ++i){
			a[i] = {R(), (short)R()};
		}
		sort(a, a + n);
		int sum = 0;
		for(int i = 0; i < n; ++i){
			if(m <= 0) break;
			int d = min(m, (int)a[i].n);
			m -= d;
			sum += a[i].c * d;
		}
		W(m ? -1 : sum);
	}
	write(1,OB,OP);
	return 0;
}