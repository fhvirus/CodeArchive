#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define MAXN 200000

int main(){OW0
	int n;
	cin >> n;
	cout << 3 * n + 4 << '\n';
	for(int i = 0; i <= n; i++){
		cout << i << ' ' << i << '\n';
		cout << i+1 << ' ' << i << '\n';
		cout << i << ' ' << i+1 << '\n';
	}
	cout << n+1 << ' ' << n+1 << '\n';
	return 0;
}