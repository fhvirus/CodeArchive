//Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define AI(x) (x).begin(),(x).end()
#define FOR(i,n) for(int i=0;i<(n);++i)
#define pb emplace_back
#define ff first
#define ss second
template<typename I> bool chmax(I &a, I b){ return a < b ? (a = b, true) : false;}

const int N = 3000;
int n, l, w;
pii p[N];
vector<int> xx, yy;

int main(){
	cin >> n >> l >> w;
	FOR(i,n){
		cin >> p[i].ff >> p[i].ss;
		xx.pb(p[i].ff);
		yy.pb(p[i].ss);
	}
	sort(p, p + n);
	sort(AI(xx)); xx.resize(unique(AI(xx)) - xx.begin());
	sort(AI(yy)); yy.resize(unique(AI(yy)) - yy.begin());

	int ans = 0;
	for(int y: yy){
		int lptr = 0, rptr = 0, cnt = 0;
		for(int x: xx){
			while(lptr < n and p[lptr].ff < x){
				if(p[lptr].ss >= y and p[lptr].ss <= y + l) --cnt;
				++lptr;
			}
			while(rptr < n and p[rptr].ff <= x + w){
				if(p[rptr].ss >= y and p[rptr].ss <= y + l) ++cnt;
				++rptr;
			}
			chmax(ans, cnt);
			if(rptr == n) break;
		}
		if(y + l >= yy.back()) break;
	}
	cout << ans << endl;
	return 0;
}