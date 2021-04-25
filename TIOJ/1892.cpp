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
#define safe ((void)0)
#define debug(...) ((void)0)
#endif
constexpr ll inf = 1e9, INF = 4e18;
const int N = 101, M = 1e9 + 7;

int n;
ll ori[N], trn[N][N], ans[N];

ll x[N][N], r[N][N], t[N][N];

void solve(int k){
	FOR(i,n) FOR(j,n) x[i][j] = trn[i][j];
	FOR(i,n) FOR(j,n) r[i][j] = (i == j);

	while(k){
		if(k & 1){
			// r = r * x;
			FOR(i,n) FOR(j,n) t[i][j] = 0;
			FOR(i,n) FOR(j,n){
				FOR(k,n) t[i][j] += r[i][k] * x[k][j] % M;
				t[i][j] %= M;
			}
			FOR(i,n) FOR(j,n) r[i][j] = t[i][j];
		}
		// x = x * x;
		FOR(i,n) FOR(j,n) t[i][j] = 0;
		FOR(i,n) FOR(j,n){
			FOR(k,n) t[i][j] += x[i][k] * x[k][j] % M;
			t[i][j] %= M;
		}
		FOR(i,n) FOR(j,n) x[i][j] = t[i][j];
		k >>= 1;
	}

	FOR(i,n){
		ans[i] = 0;
		FOR(j,n) ans[i] += r[i][j] * ori[j] % M;
		ans[i] %= M;
	}
	return;
}

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	FOR(i,n) cin >> ori[i];

	int m; cin >> m;
	for(int a, b, c; m; --m){
		cin >> a >> b >> c;
		trn[b][a] += c;
	}
	FOR(i,n) trn[i][i] = 1;

	int q; cin >> q;
	for(int k; q; --q){
		cin >> k;
		solve(k);
		FOR(i,n) cout << ans[i] << ' ';
		cout << '\n';
	}

	return 0;
}
