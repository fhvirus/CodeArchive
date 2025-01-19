// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i = 0; i < (n); ++i)
#define FOO(i,a,b) for(int i = (a); i <= (b); ++i)
#define AI(x) (x).begin(),(x).end()
template<typename I> void chmax(I &a, I b){ return a < b ? (a = b, true) : false;}
template<typename I> void chmin(I &a, I b){ return b < a ? (a = b, true) : false;}
#ifdef OWO
#define DE(args...) LKJ("[ " + string(#args) + " ]", args)
void LKJ(){ cerr<<endl;}
template<typename I, typename...T> void LKJ(I&&x,T&&...t){cerr<<x<<", ", LKJ(t...);}
template<typename I> void debug(I a,I b){ while(a < b) cerr<<*a<<" \n"[next(a) == b], ++a;}
#else
#define DE(...) 0
#define debug(...) 0
#endif
const int N = 2e5 + 225, L = 30;
int n, q;
int anc[L][N];
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> q;
	FOO(i,1,n){
		int a; cin >> a;
		anc[0][i] = a;
	}
	FOO(l,1,L-1){
		FOO(i,1,n) anc[l][i] = anc[l-1][anc[l-1][i]];
	}
	for(; q; --q){
		int k, x; cin >> k >> x;
		FOR(i,L){
			if(x>>i & 1) k = anc[i][k];
		}
		cout << k << '\n';
	}
	return 0;
}
