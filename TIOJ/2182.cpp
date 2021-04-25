#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}
inline void W(int n){char OB[12],OP=0,buf[12],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
template<typename I> bool chmax(I &a, I b){ return a < b ? (a = b, true) : false;}

#include<algorithm>
using namespace std;

const int N = 1005;
int n, m, g, dp[N], roll;

int main(){
	n = R(), m = R();
	int ans = -8e7;
	FOO(i,1,n){
		FOO(j,1,m){
			g = R();
			dp[j] = max({dp[j], dp[j-1], 0}) + g;
		}
		chmax(ans, dp[m]);
	}
	FOO(j,1,m) chmax(ans, dp[j]);
	W(ans);
	return 0;
}
