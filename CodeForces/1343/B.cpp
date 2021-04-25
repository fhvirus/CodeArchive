#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int T, n;
	cin >> T;
	while(T--){
		cin >> n;
		if(n % 4) cout << "NO\n";
		else{
			cout << "YES\n";
			for(int i = 2; i <= n; i+=2)
				cout << i << ' ';
			for(int i = 1; i <= n+1; i+=2)
				if(i != (n+2) / 2) cout << i << ' ';
			cout << '\n';
		}
	}
	return 0;
}