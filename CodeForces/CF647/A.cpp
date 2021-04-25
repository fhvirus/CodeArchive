#include<iostream>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int n;
	unsigned long long int a, b, ans;
	cin >> n;
	for(;n;--n){
		cin >> a >> b; ans = 0;
		if(a > b) swap(a, b);
		while(b > a and !(b&1)){
			b >>= 1;
			ans++;
		}
		if(b != a) cout << "-1\n";
		else cout << ans / 3 + (ans % 3 ? 1 : 0) << '\n';
	}
	return 0;
}