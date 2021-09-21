// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define OOF(i,a,b) for(int i=(a);i>=int(b);--i)
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
inline ll cdiv(ll x,ll m){return x/m+(x%m?(x<0)^(m>0):0);}
#ifdef OWO
#define safe cerr<<"\033[1;32m"<<__PRETTY_FUNCTION__<<" - "<<__LINE__<<" JIZZ\033[0m\n"
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
#else
#pragma GCC optimize("Ofast")
#define safe ((void)0)
#define debug(...) ((void)0)
#endif
const ll inf = 1e9, INF = 4e18;
const int N = 17;
int n, m, k;
inline void madd(int &a, int v){
	a += v - k;
	a += (a>>31) & k;
}
void roll(vector<int> &dp){
	vector<int> t(2<<m, 0);
	int msk = (1<<m) - 1;
	FOR(i,2<<m){
		madd(t[ (i&msk)<<1 ], dp[i]);
		madd(t[(i&msk)<<1|1], dp[i]);
	}
	FOR(i,2<<m)
		if((i & 0b111) == 0) t[i] = 0;
	t.swap(dp);
}
void solve(){
	vector<int> dp(2<<m);
	vector<int> qb(2<<m);
	FOR(i,2<<m) dp[i] = ((i & 0b111) != 0);

	const bool tak[8] = {0, 1, 1, 1, 1, 1, 1, 1};
	const bool nie[8] = {0, 0, 0, 1, 0, 1, 1, 1};

	for(int i = 1; i < n; ++i){
		for(int j = 1; j < m; ++j){
			fill(AI(qb), 0);
			
			FOR(s,2<<m){
				int d = (s >> (j-1));
				d &= 0b111;
				if(tak[d]) madd(qb[s | (1<<j)], dp[s]);
				if(nie[d]) madd(qb[s & (~(1<<j))], dp[s]);
			}

			qb.swap(dp);
		}
		roll(dp);
	}

	int ans = 0;
	FOR(i,1<<m) madd(ans, dp[i<<1|1]);
	cout << ans;
}

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m >> k;
	if(n < m) swap(n, m);
	solve();
	return 0;
}

