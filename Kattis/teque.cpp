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

struct Teque{
	deque<int> a, b;
	void atob(){ b.push_front(a.back()); a.pop_back();}
	void btoa(){ a.push_back(b.front()); b.pop_front();}
	void push_back(int i){
		b.push_back(i);
		if(b.size() > a.size()) btoa();
	}
	void push_front(int i){
		a.push_front(i);
		if(a.size() > b.size() + 1) atob();
	}
	void push_middle(int i){
		a.push_back(i);
		if(a.size() > b.size() + 1) atob();
	}
	int get(int i){
		if(a.size() > i) return a[i];
		return b[i - a.size()];
	}
} teque;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n; cin >> n;
	for(int a; n; --n){
		string s; cin >> s >> a;
		if(s == "push_back") teque.push_back(a);
		else if(s == "push_front") teque.push_front(a);
		else if(s == "push_middle") teque.push_middle(a);
		else cout << teque.get(a) << '\n';
	}
	return 0;
}
