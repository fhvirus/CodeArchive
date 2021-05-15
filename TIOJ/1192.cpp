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

struct DSU{
	int n;
	vector<int> f;
	DSU(){}
	void init(int _n){
		n = _n;
		f.resize(n + 1);
		iota(AI(f), 0);
	}
	int F(int a){ return a == f[a] ? a : f[a] = F(f[a]);}
	bool M(int a, int b){
		a = F(a), b = F(b);
		if(a == b) return false;
		f[b] = a;
		return true;
	}
} dsu;

void solve(){
	int n, l;
	cin >> n >> l;
	vector<vector<int>> tu(l + 1, vector<int>()), ow(l + 1, vector<int>());
	for(int i = 1; i <= n; ++i){
		int in;
		while(cin >> in){
			if(in == 0) break;
			tu[in].pb(i);
		}
		while(cin >> in){
			if(in == 0) break;
			ow[in].pb(i);
		}
	}

	dsu.init(n * 2);
	bool ans = true;
	for(int i = 1; i <= l / 2; ++i){
		for(int a: tu[i]) for(int b: ow[i]){
			dsu.M(a, b + n);
			dsu.M(a + n, b);
			if(dsu.F(a) == dsu.F(a + n)){
				ans = false;
				goto output;
			}
		}
	}

output:
	if(ans) cout << "Yes\n";
	else cout << "No\n";
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t; cin >> t;
	for(; t; --t) solve();
	return 0;
}
