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

struct LISAN: vector<int>{
	void done(){ sort(AI()); erase(unique(AI()), end());}
	int operator()(int v){ return lower_bound(AI(), v) - begin();}
};

void solve(int n){
	vector<pii> b;
	for(int i = 0, l, h, r; i < n; ++i){
		cin >> l >> h >> r;
		b.pb(l, h);
		b.pb(r, -h);
	}
	sort(AI(b));

	multiset<int> s;
	int cur = 0;
	s.insert(0);
	vector<pii> ans;
	for(int i = 0, j = 0; i < b.size(); i = j){
		while(j < b.size() and b[j].ff == b[i].ff){
			int h = b[j].ss;
			if(h < 0) s.erase(s.find(-h));
			else s.insert(h);
			++j;
		}
		if(*rbegin(s) != cur){
			cur = *rbegin(s);
			ans.pb(b[i].ff, cur);
		}
	}
	for(int i = 0; i < ans.size(); ++i) cout << ans[i].ff << ' ' << ans[i].ss << " \n"[i == ans.size() - 1];
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n; while(cin >> n) solve(n);
	return 0;
}
