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
 
const int kC = 62;
const int MOD = 998244353;
inline int ci(char c){ return c >= 'a' ? c - 'a' : (c >= 'A' ? c - 'A' + 26 : c - '0' + 52); }
inline void mad(int &a, int b){ a += b - MOD; a += (a>>31) & MOD; }
 
int adj[kC][kC];
int tri[kC][kC][kC];
int qua[kC][kC][kC][kC];
void init(){
	memset(adj, 0, sizeof(adj));
	memset(tri, 0, sizeof(tri));
	memset(qua, 0, sizeof(qua));
}
 
bool isPalim(string s){
	int n = s.size();
	for(int l = 0, r = n-1; l < r; ++l, --r)
		if(s[l] != s[r]) return false;
	return true;
}
 
int solve(vector<string> &s){
	debug(s);
	if(s.empty()) return 0;
	init();
	set<string> ss;
	for(auto i: s){
		if(ss.count(i)) continue;
		int a = ci(i.front()), b = ci(i.back());
		ss.insert(i);
		++adj[a][b];
		if(isPalim(i)) continue;
		reverse(AI(i));
		ss.insert(i);
		++adj[b][a];
	}
 
//	for(int i = 0; i < kC; ++i){
//		for(int j = 0; j < kC; ++j)
//			cout << adj[i][j] << ' ';
//		cout << '\n';
//	}
 
	// construct tri
	for(int u = 0; u < kC; ++u)
		for(int i = 0; i < kC; ++i) if(adj[u][i])
			for(int j = 0; j < kC; ++j) if(adj[u][j])
				for(int k = 0; k < kC; ++k) if(adj[u][k]){
					ll v = adj[i][u] * adj[j][u] * adj[k][u];
					mad(tri[i][j][k], (v % MOD));
				}
 
	// construct qua
	for(int i = 0; i < kC; ++i)
		for(int j = 0; j < kC; ++j) if(adj[i][j])
			for(int k = 0; k < kC; ++k) if(tri[i][j][k])
				for(int l = 0; l < kC; ++l)
					mad(qua[i][j][k][l], 1ll * tri[i][j][k] * tri[j][k][l] % MOD);
 
	int ans = 0;
	for(int i = 0; i < kC; ++i)
		for(int j = 0; j < kC; ++j)
			for(int k = 0; k < kC; ++k)
				for(int l = 0; l < kC; ++l) if(qua[i][j][k][l])
					mad(ans, 1ll * qua[i][j][k][l] * qua[j][i][l][k] % MOD);
 
	debug(ans);
	return ans;
}
 
signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n; cin >> n; cin.ignore();
	vector<vector<string>> bkt(11);
	string s;
	for(int i = 1; i <= n; ++i){
		getline(cin, s);
		bkt[s.length()].push_back(s);
	}
 
	int ans = 0;
	for(int i = 3; i <= 10; ++i)
		mad(ans, solve(bkt[i]));
	cout << ans;
	return 0;
}
