// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;if(n<0){OB[OP++]='-';while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<cstdlib>
#include<unordered_map>
using namespace std;
#define ff first
#define ss second
#define FOR(i,n) for(int i = 0; i < n; ++i)
#define FOO(i,a,b) for(int i=a;i<=b;++i)
const int N = 2001;
int n, a[N][N], q, r1, r2, c1, c2;
bool check(int x){
	int cnt = 0;
	FOO(i,r1,r2) FOO(j,c1,c2) if(a[i][j] == x) ++cnt;
	return cnt * 2 > (r2 - r1 + 1) * (c2 - c1 + 1);
}
void solve(){
	int r = r2 - r1 + 1, c = c2 - c1 + 1;
	auto ran = [&](){ return a[rand() % r + r1][rand() % c + c1];};
	unordered_map<int, int> eek;
	for(int i = 0; i < 1000; ++i) ++eek[ran()];
	for(auto i: eek){
		if(i.ss >= 333){
			if(check(i.ff)){
				W(i.ff);
				return;
			}
		}
	}
	W(-1);
}
int main(){
	srand(7122);
	while(n = R()){
		FOR(i,n) FOR(j,n) a[i][j] = R();
		q = R();
		FOR(i,q) r1 = R(), r2 = R(), c1 = R(), c2 = R(), solve();
	}
	write(1,OB,OP);
	return 0;
}
