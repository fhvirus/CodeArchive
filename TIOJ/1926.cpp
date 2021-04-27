// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
typedef long long ll;
#include "lib1926.h"

int main(){
	ll n, m; Init(&n, &m);
	ll l = 0, r = m;
	while(true){
		ll mid = (l + r) / 2, pos = 0;
		for(ll i = 1; i < n; ++i){
			if(!Oshietekudasai(pos, mid, i, mid))
				pos = i;
		}
		if(l + 1 == r) Report(pos, mid);
		if(mid + 1 < r and !Oshietekudasai(pos, mid, pos, mid + 1)) l = mid + 1;
		else if(l < r and !Oshietekudasai(pos, mid, pos, mid - 1)) r = mid;
		else Report(pos, mid);
	}
	return 0;
}
