// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<vector>
using namespace std;
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define OOF(i,a,b) for(int i=(a);i>=int(b);--i)

const int N = 10001, L = 30, Q = 1e6 + 1;

struct Trie{
	int ch[N * L][2], mn[N * L], tot = 1;
	void ins(int v, int p){
		int u = 0;
		for(int l = L - 1; l >= 0; --l){
			int d = v >> l & 1;
			if(!ch[u][d]) ch[u][d] = tot++;
			u = ch[u][d];
			mn[u] = p;
		}
	}
	int que(int v, int lim){
		int u = 0, ans = 0;
		for(int l = L - 1; l >= 0; --l){
			int d = (v >> l & 1) ^ 1;
			if(!ch[u][d] or mn[ch[u][d]] >= lim)
				u = ch[u][d ^ 1];
			else
				u = ch[u][d], ans |= 1 << l;
		}
		return ans;
	}
} trie;
struct Query{
	int r, v, id;
	Query(int r = 0, int v = 0, int id = 0):
		r(r), v(v), id(id){}
};

int n, q;
vector<Query> qs[N];
int ans[Q];
int a[N], s[N];

int main(){
	n = R(), q = R();
	FOR(i,n) a[i] = R();
	OOF(i,n-1,0) s[i] = a[i] ^ s[i+1];
	FOR(i,q){
		int l, r, v; l = R(), r = R(), v = R();
		qs[l].pb(r, v, i);
	}
	OOF(i,n-1,0){
		trie.ins(s[i], i);
		for(auto [r, v, id]: qs[i])
			ans[id] = trie.que(v ^ s[r], r);
	}
	FOR(i,q) W(ans[i]);
	write(1,OB,OP);
	return 0;
}
