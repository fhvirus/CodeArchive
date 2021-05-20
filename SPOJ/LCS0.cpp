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

// ref: https://github.com/phoemur/competitive-programming/blob/master/SPOJ/LCS0%20-%20Longest%20Common%20Subsequence.cpp

int lcs(string a, string b){
	int n = a.size(), m = b.size();
	if(n == 0 or m == 0) return 0;

	int w = (n + 31) >> 5;
	uint32_t chr[256][w];
	memset(chr, 0, sizeof(chr));

	for(int i = 0, j = 0, p = 1; i < n; ++i){
		chr[a[i]][j] |= p;
		p <<= 1;
		if(!p) ++j, ++p;
	}

	uint32_t bs[w];
	memset(bs, 0, sizeof(bs));

	for(int i = 0; i < m; ++i){
		uint32_t b1 = 1, b2 = 0, x, y;
		for(int j = 0; j < w; ++j){
			x = bs[j] | chr[b[i]][j];
			y = x - (bs[j] << 1 | b1 + b2);
			b1 = bs[j] >> 31;
			b2 = (y > x);
			bs[j] = x & (~y);
		}
	}

	int ans = 0;
	for(int i = 0; i < w; ++i)
		for(int v = bs[i]; v; v -= v & -v)
			++ans;
	return ans;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	string a, b; cin >> a >> b;
	if(a.size() < b.size()) swap(a, b);
	cout << lcs(a, b);
	return 0;
}
