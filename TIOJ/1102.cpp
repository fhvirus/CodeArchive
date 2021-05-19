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

void solve(int n, int m){
	m += n;
	vector<int> a(n + 1), b(n + 1);
	for(int i = 1; i <= n; ++i) cin >> b[i];
	for(int i = 1; i < n; ++i) a[i] = b[i + 1] - b[i] - 1;
	a[n] = b[1] + m - b[n] - 1;

	vector<int> dp0(4, 0), dp1(4, 0);
	dp1[1] = a[1];
	int ans = 0;
	for(int i = 2; i <= n; ++i){
		dp0[i & 3] = max(dp0[i-1 & 3], dp0[i-2 & 3] + a[i]);
		dp1[i & 3] = max(dp1[i-1 & 3], dp1[i-2 & 3] + a[i]);
	}
	cout << max(dp0[n & 3], dp1[n-1 & 3]) << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int a, b, n, m;
	while(cin >> a >> b >> n >> m and n) solve(n, m);
	return 0;
}
