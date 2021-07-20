#pragma GCC optimize("Ofast")
#define AI(x) begin(x),end(x)
#define pb emplace_back
typedef long long ll;

#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline ll R(){static char c;ll a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}

inline void PC(char c){ OB[OP++] = c; if(OP == 65536) write(1,OB,OP), OP = 0; }
inline void W(int n){static char buf[12],p;if(n==0)PC('0');p=0;if(n<0){PC('-');while(n)buf[p++]='0'-(n%10),n/=10;}else{while(n)buf[p++]='0'+(n%10),n/=10;}for(--p;p>=0;--p)PC(buf[p]);PC('\n');}
inline void GG(){ for(int i = 0; i < 13; ++i) PC("No Solution!\n"[i]); }

#include<vector>
#include<algorithm>
using namespace std;

int n, m, q;
vector<int> a, b;

signed main(){
	n = R(), m = R(), q = R();
	a.resize(n);
	for(int i = 0; i < n; ++i) a[i] = R();
	sort(AI(a));
	do{
		int v = 0;
		for(int i = 0; i < m; ++i) v += (m - i) * a[i];
		// This 'if' is the key from 30 MB to 2 MB!
		if(b.empty() or v != b.back()) b.pb(v);
	} while(next_permutation(AI(a)));
	sort(AI(b)); b.erase(unique(AI(b)), end(b));

	for(int i = 1; i <= q; ++i){
		PC('C'); PC('a'); PC('s'); PC('e'); PC(' '); PC('#'); W(i);
		ll v = R();
		if(v < b[0]){ GG(); continue; }
		auto it = lower_bound(AI(b), v + 1);
		W(*prev(it));
	}
	write(1,OB,OP);
	return 0;
}
