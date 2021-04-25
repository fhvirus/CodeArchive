#pragma Ofast
#pragma loop-opt(on)
#pragma GCC target("avx,avx2")
#define FOR(i, n) for(int i = 0; i < n; ++i)
#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 2e5 + 10;
int n;
ll a[N];

ll dq(int l, int r, bool big){
	if(r - l <= 0) return 0;
	if(r - l == 1) return a[l];
	if(r - l == 2) return -(a[l] + a[l+1]);
	ll ans = big ? -2e18 : 2e18;
	for(int m = l + 1; m < r; ++m)
		ans = big ? max(ans, -(dq(l, m, !big) + dq(m, r, !big))) : min(ans, -(dq(l, m, !big) + dq(m, r, !big)));
	return ans;
}

int main(){OW0
	cin >> n;
	FOR(i, n) cin >> a[i];
	cout << dq(0, n, true) << endl;
	return 0;
}