#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	long long int n, a, ans;
	cin >> n;
	for(;n;--n){
		cin >> a; ans = 0;
		for(;a; a &= (a-1)){
			ans += (((a&-a)<<1)-1);
		}
		cout << ans << '\n';
	}
	return 0;
}