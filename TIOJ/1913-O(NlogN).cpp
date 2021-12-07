#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n,char e){static char buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}

#include <vector>
#include <algorithm>
using namespace std;

#define pb emplace_back
#define AI(x) begin(x),end(x)

struct pii {
	int val, pos;
	pii (int v, int p):
		val(v), pos(p) {}
};

const int kN = 5005;
int n, v[kN];

vector<int> decB[kN+kN];
vector<int> incB[kN+kN];
vector<pii> dec;
vector<pii> inc;

void solve() {
	n = R();
	for (int i = 0; i < n; ++i)
		v[i] = R();

	for (int i = 0; i < n+n; ++i)
		decB[i].clear();
	for (int i = 0; i < n+n; ++i)
		incB[i].clear();
	dec.clear();
	inc.clear();
	dec.pb(kN + kN, -1);
	inc.pb(0, -1);

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		while (true) {
			auto [val, pos] = dec.back();
			if(val > v[i]) break;
			decB[val + pos].pop_back();
			dec.pop_back();
		}
		while (true) {
			auto [val, pos] = inc.back();
			if(val < v[i]) break;
			incB[val + n - pos].pop_back();
			inc.pop_back();
		}
		auto &de = decB[v[i] + i];
		auto &in = incB[v[i] + n-i];
		ans += end(de) - lower_bound(AI(de), inc.back().pos);
		ans += end(in) - lower_bound(AI(in), dec.back().pos);
		de.pb(i);
		in.pb(i);
		dec.pb(v[i], i);
		inc.pb(v[i], i);
	}

	W(ans, '\n');
	return;
}

signed main() {
	for (int t = R(); t; --t)
		solve();
	write(1, OB, OP);
	return 0;
}
