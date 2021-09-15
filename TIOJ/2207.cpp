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
	int N, k; cin >> N >> k;
	assert(1 <= N and N <= 100000);
	assert(1 <= k and k <= 3);

	if(k == 1){
		string s; cin >> s;
		for(char i: s) cout << (i == '0' ? '1' : '0');
		cout << '\n';
		return 0;
	}

	if(k == 2){
		string a, b, ans;
		ans.resize(N);
		cin >> a >> b;

		int last = 0;
		for(int i = 0; i < N; ++i){
			if(a[i] == b[i]) ans[i] = (a[i] == '0' ? '1' : '0');
			else{
				if(last == 0) ans[i] = a[i];
				else ans[i] = b[i];
				last = 1 - last;
			}
		}
		cout << ans << '\n';
		return 0;
	}

	vector<string> s(3);
	string ans;
	for(string &i: s) cin >> i;
	ans.resize(N);

	vector<int> cnt(3, 0);
	for(int i = 0; i < N; ++i){
		if(s[0][i] == s[1][i] and s[1][i] == s[2][i])
			continue;
		char c = 0;
		for(string &j: s) c ^= j[i];
		for(int j = 0; j < 3; ++j)
			if(s[j][i] == c) ++cnt[j];
	}
	vector<int> id({0, 1, 2});
	sort(AI(id), [&](int i, int j){ return cnt[i] > cnt[j]; });
	vector<int> ns(3, 0);
	while(cnt[id[0]] - 1 >= cnt[id[1]] + 1)
		++ns[id[0]], --cnt[id[0]], ++cnt[id[1]];

	for(int i = 0; i < N; ++i){
		if(s[0][i] == s[1][i] and s[1][i] == s[2][i]){
			ans[i] = (s[0][i] == '0' ? '1' : '0');
			continue;
		}
		char c = 0;
		for(string &j: s) c ^= j[i];
		for(int j = 0; j < 3; ++j)
			if(s[j][i] == c){
				if(ns[j]) ans[i] = (s[j][i] == '0' ? '1' : '0'), --ns[j];
				else ans[i] = s[j][i];
			}
	}
	cout << ans;


	return 0;
}

