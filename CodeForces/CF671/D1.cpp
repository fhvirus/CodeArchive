#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

#define justinlaiorz ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int long long
const int N = 1e5;
int t, n, a[N];

signed main(){ justinlaiorz
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	sort(a, a + n);
	cout << n/2 - (n % 2 == 0 ? 1 : 0) << '\n';
	for(int l = 0, r = n / 2; r < n; ++r, ++l){
		cout << a[r] << ' ';
		if(l < n / 2) cout << a[l] << ' ';
	}
	return 0;
}