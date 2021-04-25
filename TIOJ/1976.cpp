// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<algorithm>
using namespace std;
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}

const int N = 100001;
int l[N], r[N], c[N];
int lisan[N * 3], m;
int in[N * 3], ou[N * 3];

int main(){
	int n = R();
	for(int i = 0; i < n; ++i){
		lisan[m++] = l[i] = R();
		lisan[m++] = r[i] = R();
		lisan[m++] = r[i] + 1;
		c[i] = R();
	}
	sort(lisan, lisan + m);
	m = unique(lisan, lisan + m) - lisan;
	for(int i = 0; i < n; ++i){
		l[i] = lower_bound(lisan, lisan + m, l[i]) - lisan;
		r[i] = lower_bound(lisan, lisan + m, r[i]) - lisan;
		in[l[i]] += c[i];
		ou[r[i] + 1] += c[i];
	}
	int ans = 0, sum = 0, pre = 0;
	for(int i = 0; i < m; ++i){
		sum += in[i];
		sum -= ou[i];
		pre = max(ou[i], pre + ou[i]);
		chmax(ans, sum + pre);
	}
	W(ans);
	return 0;
}
