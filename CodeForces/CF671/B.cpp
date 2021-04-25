#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

#define justinlaiorz ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int long long
int t, n;
vector<int> jizz(32);

signed main(){ justinlaiorz
	for(int i = 1; i < 32; ++i)
		jizz[i] = (1ll<<(i-1)) * ((1ll<<i) - 1);
	for(int i = 1; i < 32; ++i)
		jizz[i] += jizz[i-1];
	// for(int i: jizz) cout << i << '\n';
	cin >> t;
	for(; t; --t){
		cin >> n;
		cout << upper_bound(jizz.begin(), jizz.end(), n) - jizz.begin() - 1 << '\n';
	}
	return 0;
}