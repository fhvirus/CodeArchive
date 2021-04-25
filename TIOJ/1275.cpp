// Knapsack DP is harder than FFT.
#ifndef OWO
#include<bits/stdc++.h>
#endif
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define OOF(i,a,b) for(int i=(a);i>=int(b);--i)
#define AI(x) (x).begin(),(x).end()
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
template<class V>void lisan(V&v){sort(AI(v));v.erase(unique(AI(v)),v.end());}
template<class V,class T>int lspos(const V&v,T x){return lower_bound(AI(v),x)-v.begin();}
template<class...T>void RI(T&...t){(...,(cin>>t));}
template<class...T>void PL(T...t){int c=sizeof...(T);if(!c){cout<<'\n';return;}(...,(cout<<t<<(--c?' ':'\n')));}
constexpr inline ll cdiv(ll x,ll m){return x/m+(x%m?(x<0)^(m>0):0);}
constexpr inline ll mpow(ll x,ll e,ll m){ll r=1;for(x%=m;e;e/=2,x=x*x%m)if(e&1)r=r*x%m;return r;}
#ifdef OWO
#define safe cerr<<"\033[1;32m"<<__PRETTY_FUNCTION__<<" - "<<__LINE__<<" JIZZ\033[0m\n"
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}
template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
#else
#pragma GCC optimize("Ofast")
#include "lib1275.h"
#define safe ((void)0)
#define debug(...) ((void)0)
#endif
constexpr ll inf = 1e9, INF = 4e18;
template<typename T> using rbt = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
int GetBestPosition(int N, int C, int R, int *K, int *S, int *E){
	rbt<pii> tr;
	FOR(i,N) tr.insert({i, i});

	vector<pii> rounds;
	FOR(i,C){
		auto l = tr.find_by_order(S[i]), r = tr.find_by_order(E[i]), e = next(r);
		rounds.pb(l->ff, r->ss);
		for(auto i = l; i != e; i = tr.erase(i));
		tr.insert(rounds.back());
	}

	vector<int> rspan(N);
	OOF(i,N-2,0) rspan[i] = (K[i] < R ? rspan[i+1]+1 : 0);

	vector<int> ans(N + 1);
	for(auto i: rounds)
		if(rspan[i.ff] >= i.ss - i.ff) ++ans[i.ff], --ans[i.ss + 1];
	FOO(i,1,N) ans[i] += ans[i-1];
	return max_element(AI(ans)) - ans.begin();
}

#ifdef OWO
const int N = 1e5 + 225;
int n, c, r, k[N], s[N], e[N];
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> c >> r;
	for(int i = 0; i < n - 1; ++i) cin >> k[i];
	for(int i = 0; i < c; ++i) cin >> s[i] >> e[i];
	cout << GetBestPosition(n, c, r, k, s, e) << '\n';
	return 0;
}
#endif
