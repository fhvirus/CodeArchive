#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
const ll M = 1e9 + 7;

ll mpow(ll x, ll e){
	ll ans = 1;
	while(e) (e&1)&&(ans = ans * x % M), x = x * x % M, e >>= 1;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n, x, pos;
	cin >> n >> x >> pos;

	int larger = 0, smaller = 0, times = 0;
	int l = 0, r = n, m;
	while(l < r){
		m = (l + r) / 2;
		if(m == pos){
			l = m + 1;
		} else if(m < pos){
			l = m + 1;
			smaller ++;
		} else {
			r = m;
			larger ++;
		}
		times++;
	}

	// cout << times << ' ' << smaller << ' ' << larger << '\n';

	vector<ll> frac(n + 1);
	frac[0] = 1;
	for(int i = 1; i <= n; ++i)
		frac[i] = frac[i-1] * i % M;

	if(n - x < larger or x - 1 < smaller){
		cout << 0;
		return 0;
	}

	ll ans = 1;
	ans = (ans * frac[n - x]) % M;
	ans = (ans * mpow(frac[n - x - larger], M - 2)) % M;
	ans = (ans * frac[x - 1]) % M;
	ans = (ans * mpow(frac[x - 1 - smaller], M - 2)) % M;
	ans = (ans * frac[n - times]) % M;
	// ans = ans * frac[n - x] / frac[n - x - larger];
	// cout << ans << endl;
	// ans = ans * frac[x - 1] / frac[smaller];
	// cout << ans << endl;

	cout << ans;
	return 0;
}