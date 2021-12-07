#include<iostream>
#include<algorithm>
using namespace std;

const int kN = 30003;
int n, m, a[kN];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	/*
	 * 觀察那些我有用到的邊
	 * 只要有繞一圈就可以整圈拔掉
	 * 注意！不是經過的點，是邊
	 */

	while(cin >> n >> m){
		for(int i = 0; i < n; ++i) a[i] = 0;
		for(int l, r, i = 0; i < m; ++i){
			cin >> l >> r;
			if(l <= r) ++a[l], --a[r];
			else ++a[0], --a[r], ++a[l];
		}
		for(int i = 1; i < n; ++i) a[i] += a[i-1];
		
		int mn = m;
		for(int i = 0; i < n; ++i)
			if(mn > a[i]) mn = a[i];
		cout << mn * n << '\n';
	}
	
	return 0;
}
