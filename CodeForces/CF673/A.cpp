#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int t, n, k, a[1000];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> t;
	for(; t; --t){
		cin >> n >> k;
		for(int i = 0; i < n; ++i) cin >> a[i];
		int mn = a[0], mnid = 0;
		for(int i = 0; i < n; ++i) if(a[i] < mn) mnid = i, mn = a[i];
		int ans = 0;
		for(int i = 0; i < n; ++i) if(i != mnid) ans += (k - a[i]) / mn;
		cout << ans << '\n';
	}
}