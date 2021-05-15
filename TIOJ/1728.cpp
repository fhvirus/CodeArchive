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

#ifdef OWO
const int N = 100001, L = 17;
#else
const int N = 10000001, L = 24;
#endif

int cnt[N];
int st[L][N];

int mx(int a, int b){
	if(cnt[a] != cnt[b]) return cnt[a] > cnt[b] ? a : b;
	return a > b ? a : b;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cnt[0] = 500;
	for(int i = 1; i < N; ++i)
		for(int j = i; j < N; j += i)
			++cnt[j];

	for(int i = 1; i < N; ++i) st[0][i] = i;
	for(int l = 1; l < L; ++l)
		for(int i = 0; i + (1<<l) - 1 < N; ++i)
			st[l][i] = mx(st[l-1][i], st[l-1][i + (1<<(l-1))]);

	int a, b, d;
	while(cin >> a >> b){
		if(a > b) swap(a, b);
		d = __lg(b - a + 1);
		cout << mx(st[d][a], st[d][b - (1<<d) + 1]) << '\n';
	}
	return 0;
}
