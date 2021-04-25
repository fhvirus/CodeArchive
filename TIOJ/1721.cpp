#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n, char e){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}

#include<vector>
#include<algorithm>
using namespace std;
#define FOR(i,n) for(int i = 0; i < n; ++i)
#define pb emplace_back
#define AI(x) begin(x),end(x)

const int N = 1e5 + 225;
int n, a[N];
int rgt[N];
int stk[N], top;

void solve(){
	FOR(i,n) a[i] = R();

	top = 0;
	for(int i = n-1; i >= 0; --i){
		while(top > 0 and a[stk[top-1]] < a[i]) --top;
		rgt[i] = (top == 0 ? n - i : stk[top-1] - i + 1);
		stk[top++] = i;
	}

	top = 0;
	for(int i = 0; i < n; ++i){
		while(top > 0 and a[stk[top-1]] < a[i]) --top;
		W((top == 0 ? i + 1 : i - stk[top-1] + 1) + rgt[i] - 1, " \n"[i == n-1]);
		stk[top++] = i;
	}
}

int32_t main(){
	while(n = R()) solve();
	write(1,OB,OP);
	return 0;
}
