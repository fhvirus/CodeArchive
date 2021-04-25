#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define MAXN 200000

int main(){OW0
	long long T, a, b, n, ans;
	cin >> T;
	for(;T;--T){
		cin >> a >> b >> n;
		ans = 0;
		if(a > b) swap(a, b);
		while(a <= n and b <= n){
			a += b;
			if(a > b) swap(a, b);
			ans++;
		}
		cout << ans << '\n';
	}
	return 0;
}