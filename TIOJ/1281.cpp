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

const int MOD = 1e9+7;
const int P1 = 11;
const int Q1 = 818181824;
const int P2 = 13;
const int Q2 = 153846155;
const int kN = 100001;

inline int mad(int u, int v){
	u += v - MOD;
	u += MOD & (u>>31);
	return u;
}
inline int mul(int u, int v){
	return (ll) u * v % MOD;
}

int n; string s;
int p1[kN], q1[kN], h1[kN];
int p2[kN], q2[kN], h2[kN];

unordered_set<ll> us;
int check(int len){
	us.clear();
	for(int i = 1; i+len-1 <= n; ++i){
		int c1 = mul(mad(h1[i+len-1], MOD-h1[i-1]), q1[i-1]);
		int c2 = mul(mad(h2[i+len-1], MOD-h2[i-1]), q2[i-1]);
		ll c = (ll) c1 * MOD + c2;
		if(us.count(c)) return i;
		us.insert(c);
	}
	return -1;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> s; n = s.size(); s = ' ' + s;

	p1[0] = 1; for(int i = 1; i < n; ++i) p1[i] = mul(p1[i-1], P1);
	q1[0] = 1; for(int i = 1; i < n; ++i) q1[i] = mul(q1[i-1], Q1);
	for(int i = 1; i <= n; ++i) h1[i] = mad(h1[i-1], mul(s[i]-'a', p1[i-1]));

	p2[0] = 1; for(int i = 1; i < n; ++i) p2[i] = mul(p2[i-1], P2);
	q2[0] = 1; for(int i = 1; i < n; ++i) q2[i] = mul(q2[i-1], Q2);
	for(int i = 1; i <= n; ++i) h2[i] = mad(h2[i-1], mul(s[i]-'a', p2[i-1]));

	int len = 0, pos = 0;
	for(int l = 16; l >= 0; --l)
		if(len + (1<<l) < n){
			int d = check(len + (1<<l));
			if(d != -1){
				len += (1<<l);
				pos = d;
			}
		}

	for(int i = 0; i < len; ++i)
		cout << s[pos + i];
	
	return 0;
}
