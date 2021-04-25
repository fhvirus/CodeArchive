#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int T, n, ans;
	cin >> T;
	while(T--){
		cin >> n;
		ans = 1 << n;
		for(int i = n-1; i >= n / 2; i--) ans -= 1<<i;
		for(int i = n/2 - 1; i >= 1; i--) ans += 1<<i;
		cout << ans <<'\n';
	}
	return 0;
}