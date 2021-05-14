
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

const int N = 25;
int n, a[N][N], d[N];

void swaprow(int i, int j){
	if(i == j) return;
	for(int k = 0; k < n; ++k)
		swap(a[i][k], a[j][k]);
	swap(d[i], d[j]);
}
void solve(){
	cin >> n;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j) a[i][j] = 0;
		int m; cin >> m;
		for(int j = 0; j < m; ++j){
			int k; cin >> k;
			a[i][k] = 1;
		}
		cin >> d[i];
	}

	for(int i = 0; i < n; ++i){
		// find a valid row and move it
		for(int j = i; j < n; ++j)
			if(a[j][i] != 0){
				swaprow(i, j);
				break;
			}
		// cancel rows
		for(int j = i + 1; j < n; ++j){
			if(a[j][i] == 0) continue;
			int g = __gcd(a[i][i], a[j][i]);
			int ta = a[j][i] / g, tb = a[i][i];
			for(int k = i; k < n; ++k)
				a[j][k] = tb * a[j][k] - ta * a[i][k];
			d[j] = tb * d[j] - ta * d[i];
		}
	}

	for(int i = n-1; i >= 0; --i){
		for(int j = i + 1; j < n; ++j)
			d[i] -= d[j] * a[i][j];
		d[i] /= a[i][i];
	}
	for(int i = 0; i < n; ++i)
		cout << d[i] << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int k; cin >> k;
	for(; k; --k) solve();
	return 0;
}
