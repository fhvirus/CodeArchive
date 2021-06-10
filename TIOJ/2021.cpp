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

const int M = 1e9 + 7;
using Mat  = vector<vector<ll>>;

Mat operator*(Mat a, Mat b){
	int n = a.size();
	Mat r(n, vector<ll>(n, 0));
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j){
			for(int k = 0; k < n; ++k)
				r[i][j] += a[i][k] * b[k][j] % M;
			r[i][j] %= M;
		}
	return r;
}

Mat mpow(Mat x, ll e){
	int n = x.size();
	Mat r = x;
	for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) r[i][j] = (i == j);
	while(e > 0){
		if(e & 1) r = r * x;
		x = x * x;
		e >>= 1;
	}
	return r;
}

ll f(ll n){
	static const Mat trans({
		{1, 1, 0},
		{1, 0, 0},
		{1, 0, 1}
	});
	Mat r = mpow(trans, n);
	return (r[2][0] + r[2][1] + r[2][2]) % M;
}
ll f2(ll n){
	static const Mat trans({
		{0, 1, 0, 0},
		{1, 1, 2, 0},
		{0, 1, 1, 0},
		{1, 1, 2, 1}
	});
	Mat r = mpow(trans, n);
	return (r[3][1] + r[3][3]) % M;
}

ll solve(ll n){
	--n;
	ll ans = (f2(n) - f(n) + M) % M;
	return ans * ((M + 1) / 2) % M;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n; cin >> n;
	for(ll s, t; n; --n){
		cin >> s >> t;
		cout << (solve(t) - solve(s-1) + M) % M << '\n';
	}
	return 0;
}
