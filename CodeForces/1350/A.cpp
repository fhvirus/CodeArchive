#include<iostream>
#include<algorithm>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){eek
	int T;
	cin >> T;
	while(T--){
		int n, m;
		cin >> n >> m;
		m--;
		for(int i = 2; i <= n; i++){
			if(n % i == 0){
				n += i;
				break;
			}
		}
		n += 2 * m;
		cout << n << '\n';
	}
	return 0;
}