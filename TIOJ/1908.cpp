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
const int N = 22, C = 50000;
int n;
vector<int> valid;
int mp[1<<N], cnt;
vector<int> adj[C];
bool eek(int a, int b){
	return (a & b) || (a & b >> 1) || (a & b << 1);
}
void dfs(int p, int u, int i, vector<int> &adj){
	if(i == n){
		adj.pb(mp[u]);
		return;
	}

	dfs(p, u, i + 1, adj);

	u |= (1<<i);

	if((u & (u>>1)) == 0 and !eek(p, u))
		dfs(p, u, i + 1, adj);
}
void prepare(){
	FOR(i,1<<n)
		if((i & (i>>1)) == 0)
			valid.pb(i);
	FOR(i,valid.size()) mp[valid[i]] = i;
	FOR(i,valid.size()) dfs(valid[i], 0, 0, adj[i]);
}

int a[N][N];
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	FOR(i,n) FOR(j,n) cin >> a[i][j];

	prepare();
	
	vector<int> dp(valid.size(), 0);
	vector<int> qb(valid.size(), 0);

	FOR(r,n){
		fill(AI(qb), 0);
		FOR(i,valid.size()){
			int u = valid[i];
			int s = 0;
			FOR(k,n) if(u >> k & 1) s += a[r][k];
			dp[i] += s;
			for(int j: adj[i])
				chmax(qb[j], dp[i]);
		}
		qb.swap(dp);
	}

	cout << *max_element(AI(dp));

	return 0;
}
