// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
typedef long long ll;
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll n; cin >> n;

	int r = sqrt(n);
	vector<char> miu(r + 1, 0);
	for(int i = 2; i <= r; ++i){
		if(miu[i] != 0) continue;
		for(int j = i; j <= r; j += i)
			++miu[j];
	}
	for(int i = 2; i * i <= r; ++i)
		for(int j = i * i; j <= r; j += i * i)
			miu[j] = 0;

	ll ans = 0;
	for(ll i = 2; i <= r; ++i){
		if(miu[i] != 0) miu[i] = (miu[i] % 2 ? -1 : 1);
		ans -= n / (i * i) * miu[i];
	}
	cout << ans;
	return 0;
}
