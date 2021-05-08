// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
using namespace std;
typedef long long ll;
const int N = 100000;

ll dis[N];
int k[N], id[N];

int main(){
	int n = R();
	for(int i = 0; i < n; ++i){
		ll x = R(), y = R(); k[i] = R();
		dis[i] = x * x + y * y;
		id[i] = i;
	}
	sort(id, id + n, [&](int a, int b){ return dis[a] < dis[b];});
	ll ans = 0, sum = 0;
	for(int i = 0, j; i < n; ++i){
		for(j = i; j < n and dis[id[j]] == dis[id[i]]; ++j)
			sum += k[id[j]];
		if(sum < 0) sum = 0;
		ans = max(ans, sum);
		i = j - 1;
	}
	W(ans);
	return 0;
}
