#include<iostream>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){eek
	int T, n, k;
	cin >> T;
	while(T--){
		cin >> n >> k;
		if(n < k) cout << "NO\n";
		else if((n-(k-1))%2 == 1){
			cout << "YES\n";
			for(int i = 0; i < k-1; i++)
				cout << "1 ";
			cout << n-(k-1) << '\n';
		} else if(2*(k-1) < n and (n-2*(k-1))%2 == 0){
			cout << "YES\n";
			for(int i = 0; i < k-1; i++)
				cout << "2 ";
			cout << n-2*(k-1) << '\n';
		} else {
			cout << "NO\n";
		}
	}
	return 0;
}