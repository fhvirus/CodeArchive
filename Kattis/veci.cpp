#include<iostream>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	string in;
	cin >> in;
	if(next_permutation(in.begin(), in.end())){
		cout << in;
	} else {
		cout << 0;
	}
	return 0;
}