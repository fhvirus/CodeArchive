#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

#define justinlaiorz ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int long long
const int N = 1e5;
int t, n, a[N], eek[N], p;

signed main(){ justinlaiorz
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	sort(a, a + n);
	for(int l = 0, r = n/2; r < n; ++l, ++r){
		eek[p++] = a[r];
		if(l < n/2) eek[p++] = a[l];
	}
	int ans = 0;
	for(int i = 1; i < n-1; ++i)
		if(eek[i] < eek[i-1] and eek[i] < eek[i+1]) ++ans;
	cout << ans << '\n';
	for(int i = 0; i < n; ++i)
		cout << eek[i] << ' ';
	return 0;
}