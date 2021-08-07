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

int N;
pii a[kN];
int ans;

void solve(int l, int r){
	if(l + 1 == r) return;
	int m = (l + r) / 2;
	solve(l, m); solve(m, r);

	int lp = l, rp = m, sum = 0;
	for(; lp < m or rp < r; ){
		if(lp == m or (rp < r and a[lp].ss > a[rp].ss)){
			mad(ans, 1ll * (lp - l) * (1ll * a[rp].ff * a[rp].ss % MOD) % MOD);
			mad(ans, MOD - sum);
			++rp;
		} else {
			mad(sum, 1ll * a[lp].ff * a[lp].ss % MOD);
			++lp;
		}
	}
	inplace_merge(a + l, a + m, a + r, [](pii i, pii j){ return i.ss < j.ss; });
}

signed main(){
	N = R();
	for(int i = 0; i < N; ++i){
		a[i].ff = R();
		a[i].ss = R();
	}
	sort(a, a + N);
	solve(0, N);
	W(ans);
	return 0;
}
