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

typedef tuple<int, int, int> tii;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n, m, x, y;
	while(cin >> n >> m >> x >> y){
		int l = y-1, r = m-y;
		int u = x-1, d = n-x;
		int s = (l xor r xor u xor d);
		if(s == 0){
			cout << "No winning strategy.\n";
			continue;
		}

		tii ans(-1, -1, -1); int e;
		e = u - (s xor u);
		if(u >= e and e >= 0) ans = max(ans, tii(m*e, 1, -e));
		e = d - (s xor d);
		if(d >= e and e >= 0) ans = max(ans, tii(m*e, 1, e-n));
		e = l - (s xor l);
		if(l >= e and e >= 0) ans = max(ans, tii(n*e, 0, -e));
		e = r - (s xor r);
		if(r >= e and e >= 0) ans = max(ans, tii(n*e, 0, e-m));

		auto [cnt, dir, pos] = ans; pos = -pos;
		cout << (dir ? "horizontal " : "vertical ")
			<< pos << ' ' << cnt << '\n';
	}
	return 0;
}

