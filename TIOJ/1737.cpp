// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<utility>
#include<set>
using namespace std;
typedef pair<int,int> pii;
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
const int N = 1e5 + 225;
int n, k, t[N], a[N];
int l[N], r[N];
long long sum;

void del(int i){
	l[r[i]] = l[i];
	r[l[i]] = r[i];
}

int main(){
	n = R(), k = R();
	FOO(i,1,n) t[i] = R();
	FOO(i,2,n) a[i] = t[i] - t[i-1];
	FOO(i,2,n) l[i] = i-1, r[i] = i+1;

	set<pii> s;
	FOO(i,2,n) s.emplace(a[i], i);

	FOR(_,k){
		auto [val, i] = *begin(s);
		s.erase(begin(s));
		
		sum += val;
		a[i] = -a[i];
		int cnt = 0;
		if(l[i] != 1){
			++cnt;
			a[i] += a[l[i]];
			s.erase({a[l[i]], l[i]});
			del(l[i]);
		}
		if(r[i] != n + 1){
			++cnt;
			a[i] += a[r[i]];
			s.erase({a[r[i]], r[i]});
			del(r[i]);
		}
		if(cnt == 2)
			s.emplace(a[i], i);
		else del(i);
	}
	W(sum);
	return 0;
}
