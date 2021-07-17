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
	int n; cin >> n;
	vector<int> a(n); for(int &i: a) cin >> i;
	vector<int> b(n); for(int &i: b) cin >> i;

	// reverse so then I can greedy from back
	reverse(AI(a));
	reverse(AI(b));

	vector<int> lisan(a);
	sort(AI(lisan)); lisan.erase(unique(AI(lisan)), end(lisan));
	for(int &i: a) i = lower_bound(AI(lisan), i) - begin(lisan);
	for(int &i: b) i = lower_bound(AI(lisan), i) - begin(lisan);

	vector<int> pos(n), p(n);
	for(int i = 0; i < n; ++i) pos[b[i]] = i;
	for(int i = 0; i < n; ++i) p[i] = pos[a[i]];

	// find LIS for p
	vector<int> dp;
	vector<vector<int>> sc;
	dp.pb(-1); sc.pb(1, -1);

	for(int i = 0; i < n; ++i){
		int v = p[i];
		if(v > dp.back()){
			dp.pb(v);
			sc.pb(1, i);
			continue;
		}
		int j = lower_bound(AI(dp), v) - begin(dp);
		dp[j] = v;
		sc[j].pb(i);
	}

	int len = dp.size() - 1, lst = n + 1, lp = n + 1;
	vector<int> ans(len, 0);

	// This phase is O(n) amortized
	for(int i = len; i > 0; --i){
		int cur = -1;
		for(int j: sc[i]){
			if(j < lst and p[j] < lp)
				if(cur == -1 or a[cur] < a[j]) cur = j;
		}
		ans[i-1] = a[cur];
		lst = cur;
		lp = p[cur];
	}

	reverse(AI(ans));
	for(int i = 0; i < len; ++i)
		cout << lisan[ans[i]] << " \n"[i == len - 1];
	return 0;
}

/* Bonus testcase:
10
5 13 14 17 16 12 11 0 7 2
12 7 2 13 11 0 16 17 5 14

Output should be:
13 11 0

If you get:
12 7 2

then it's because you greedy'ed wrong dir.
*/
