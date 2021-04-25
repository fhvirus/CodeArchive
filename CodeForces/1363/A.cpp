#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int T, n, x, a, odd, even;
	for(cin >> T; T; --T){
		cin >> n >> x;
		odd = even = 0;
		for(int i = 0; i < n; i++){
			cin >> a;
			if(a & 1) odd++;
			else even++;
		}
		bool ans = false;
		for(int i = 1; i <= odd and i <= x; i+=2){
			if(x - i <= even) ans = true;
		}
		cout << (ans ? "Yes\n" : "No\n");
	}
	return 0;
}