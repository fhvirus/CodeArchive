// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	ll n; cin >> n;

	int r = sqrt(n);
	vector<int> primes, miu(r + 1, 0);
	vector<bool> np(r + 1, false);
	np[0] = np[1] = true;
	miu[1] = 1;
	for(int i = 2; i <= r; ++i){
		if(!np[i]) primes.pb(i), miu[i] = -1;
		for(int p: primes){
			if(i * p > r) break;
			np[i * p] = true;
			if(i % p == 0) break;
			miu[i * p] = -miu[i];
		}
	}

	ll ans = 0;
	for(ll i = 2; i <= r; ++i)
		ans -= n / (i * i) * miu[i];
	cout << ans;

	return 0;
}
