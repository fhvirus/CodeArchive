#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
#include<utility>
using namespace std;

const int kN = 100001;
int N;
pair<int, int> a[kN];

int main(){
	N = R();
	for(int x, y, h, i = 0; i < N; ++i){
		x = R(); y = R(); h = R();
		a[i] = pair<int, int>(x*x + y*y, -h);
	}
	sort(a, a + N);
	int ans = 0, cur = a[N-1].second;
	for(int i= N-2; i >= 0; --i){
		ans = max(ans, cur - a[i].second);
		cur = max(cur, a[i].second);
	}
	W(ans);
}
