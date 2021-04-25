#include<iostream>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){eek
	int T, n;
	cin >> T;
	while(T--){
		cin >> n;
		int tmp = n, cnt = 0;
		while(tmp){
			if(tmp%10) cnt++;
			tmp /= 10;
		}
		cout << cnt << '\n';
		tmp = 1;
		while(n){
			if(n%10)cout << (n%10) * tmp <<' ';
			tmp*=10;
			n/=10;
		}
		cout << '\n';
	}
	return 0;
}