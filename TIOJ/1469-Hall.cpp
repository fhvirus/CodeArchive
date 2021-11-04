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

inline int siz(string s){
	if(s == "XXL") return 0;
	else if(s == "XL") return 1;
	else if(s == "L") return 2;
	else if(s == "M") return 3;
	else if(s == "S") return 4;
	else if(s == "XS") return 5;
	else assert(0);
}

int N, M, sos[1 << 6];

void solve(){
	N /= 6;
	fill(sos, sos+(1<<6), 0);
	for(int i = 0; i < M; ++i){
		int k = 0;
		for(int j = 0; j < 2; ++j){
			string in; cin >> in;
			k |= 1 << siz(in);
		}
		++sos[k];
	}
	for(int i = 0; i < 6; ++i)
		for(int j = 0; j < (1<<6); ++j)
			if(j>>i & 1) sos[j] += sos[j ^ (1<<i)];
	bool ans = true;
	for(int j = 0; j < (1<<6); ++j)
		ans &= (sos[j] <= N * __builtin_popcount(j));
	cout << (ans ? "YES\n" : "NO\n");
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	while(cin >> N >> M) solve();
	return 0;
}

