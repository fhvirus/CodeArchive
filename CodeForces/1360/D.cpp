#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

inline int min(int a, int b){
	return a < b ? a : b;
}

int main(){OW0
	int t, n, k, ans;
	cin >> t;
	for(;t;t--){
		cin >> n >> k;
		ans = 1e9 + 10;
		for(int i = 1; i * i <= n; i++){
			if(n % i == 0){
				if(i <= k) ans = min(ans, n/i);
				if(n/i <= k) ans = min(ans, i);
			}
		}
		cout << ans << endl;
	}
	return 0;
}