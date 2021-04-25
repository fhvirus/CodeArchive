#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int k;
	cin >> k;
	for(int i = 0; i < k; i++){
		for(int j = 0; j < k; j++){
			if(!(i&j))
				cout << "# ";
			else
				cout << "  ";
		}
		cout << '\n';
	}
	return 0;
}