#include<iostream>
#include<cmath>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int x, ans = 0;
	cin >> x;
	int s = sqrt(x);
	for(int i = 2; i <= s and i <= x and x != 1; i++){
		while(x % i == 0){
			x /= i;
			ans++;
		}
	}
	ans += (x != 1);
	cout << ans;
	return 0;
}