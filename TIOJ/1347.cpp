// Knapsack DP is harder than FFT.
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

#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(ll n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}

const int kN = 1000001;
const ll inf = 1e18;
const __int128 INF = 1e18;

constexpr ll lpow(ll x, int e){
	if(x == 0) return 0;
	if(e == 2) return x * x;
	if(x < 0) x = -x;
	if(e == 1) return x;
	ll r = 1;
	while(e){
		if(e & 1)
			r = min((__int128) r * x, INF);
		x = (ll) min((__int128) x * x, INF);
		e >>= 1;
	}
	return r;
}
constexpr double dpow(double x, int e){
	if(x == 0) return 0;
	if(e == 2) return x * x;
	if(x < 0) x = -x;
	if(e == 1) return x;
	double r = 1;
	while(e){
		if(e & 1) r = r * x;
		x = x * x;
		e >>= 1;
	}
	return r;
}

int n, k, p;
pair<ll, int> w[kN];
ll dp[kN];
pii sc[kN];

ll we(int i, int j){
	return w[i].ff - w[i].ss - w[j].ff;
}
double dost(int j, int i){
	return dp[j] + dpow(we(i, j) - k, p);
}
int inter(int a, int b, int i){ 
	int l = i, r = n + 1, m;
	while(l < r){
		m = (l + r) / 2;
		if(dost(b, m) <= dost(a, m)) r = m;
		else l = m + 1;
	}
	return l;
}

signed main(){
	n = R(), k = R(), p = R();
	for(int i = 1; i <= n; ++i) w[i].ff = R();
	for(int i = 1; i < n; ++i) w[i].ss = R(), w[i].ff = w[i-1].ff + w[i].ff + w[i].ss;
	w[n].ff += w[n-1].ff, w[n].ss = 0;

	int he, ta; he = ta = 0;
	for(int i = 1; i <= n; ++i){
		int eek = ta - he > 0 ? inter(sc[ta-1].ff, i-1, i) : -1;
		while(he < ta and eek <= sc[ta-1].ss) --ta, eek = inter(sc[ta-1].ff, i-1, i);

		if(he == ta) sc[ta++] = pii(i-1, 1);
		else if(eek <= n) sc[ta++] = pii(i-1, eek);

		while(ta - he > 1 and sc[he+1].ss <= i) ++he;

		auto &[j, jl] = sc[he];
		dp[i] = dp[j] + lpow(we(i, j) - k, p);
	}
	W(dp[n]);
	return 0;
}
