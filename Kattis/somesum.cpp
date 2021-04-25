#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int n;
	cin >> n;
	if(n == 100) cout << "Odd";
	else if(n % 2 == 1) cout << "Either";
	else cout << (n/2%2 == 0 ? "Even" : "Odd");
	return 0;
}