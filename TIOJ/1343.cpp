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

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	int N; cin >> N;
	vector<pii> mast(N);
	for(auto &[h, k]: mast)
		cin >> h >> k;
	sort(AI(mast));

	multiset<int> ms;
	ms.insert(0);

	for(auto &[h, k]: mast){
		auto it = ms.lower_bound(h - k);
		auto pr = prev(it);
		if(it != end(ms)){
			k -= h - *it;
			ms.insert(h);
			if(*it) ms.erase(it);
		}
		if(k > 0){
			if(*pr){
				k = k + *pr;
				ms.erase(pr);
			}
			ms.insert(k);
		}
	}

	ll ans = 0, cnt = ms.size(), lst = 0;
	for(int v: ms){
		ans += cnt * (cnt-1) / 2 * (v - lst);
		lst = v;
		--cnt;
	}
	cout << ans << '\n';
	return 0;
}
