// Knapsack DP is harder than FFT.
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
#ifdef OWO
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
#else
#pragma GCC optimize("Ofast")
#define debug(...) ((void)0)
#endif

const int kN = 1000001;
const int MOD = 1e9 + 9;

inline void mad(int &a, int b){
	a += b - MOD;
	a += MOD & (a>>31);
}
struct LISAN: vector<int> {
	void done(){ sort(AI()); erase(unique(AI()), end()); }
	int operator() (int a){ return lower_bound(AI(), a) - begin(); }
};
struct BIT {
	int n; vector<int> val;
	BIT(int n = 0): n(n), val(n+1, 0) {}
	void add(int p, int v){ for(++p; p <= n; p += p&-p) mad(val[p], v); }
	int query(int p){
		int ans = 0;
		for(++p; p; p -= p&-p) mad(ans, val[p]);
		return ans;
	}
};

int N;
pii a[kN];
LISAN lisan;

signed main(){
	N = R();
	for(int i = 0; i < N; ++i){
		a[i].ff = R();
		a[i].ss = R();
		lisan.pb(a[i].ss);
	}
	sort(a, a + N);
	lisan.done();

	int ans = 0;
	BIT sum(lisan.size()), cnt(lisan.size());
	for(int i = 0; i < N; ++i){
		auto [w, h] = a[i];
		int p = lisan(h);
		int s = 1ll * w * h % MOD;
		mad(ans, MOD - sum.query(p));
		mad(ans, 1ll * s * cnt.query(p) % MOD);
		sum.add(p, s);
		cnt.add(p, 1);
	}
	W(ans);
	return 0;
}
